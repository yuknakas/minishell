/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:06:47 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/19 17:11:56 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_cmd_with_redir(t_cmd *cmd, t_minishell *sh)
{
	int	result;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (pex_perror("dup"), 1);
	result = execute_builtin(cmd, sh);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (result != -1)
		return (result);
	return (execute_external_command(cmd, sh));
}

int	execute_single_command(t_cmd *cmd, t_minishell *sh)
{
	int	result;

	if (cmd->argv == NULL || cmd->argv[0] == NULL)
		return (0);
	if (cmd->rd != NULL)
		return (exec_cmd_with_redir(cmd, sh));
	else
	{
		result = execute_builtin(cmd, sh);
		if (result != -1)
			return (result);
	}
	return (execute_external_command(cmd, sh));
}

static void	clean_child(char *path, char **envp, t_cmd *cmd)
{
	t_redir	*rd;

	free(path);
	_freearr(envp);
	rd = cmd->rd;
	while (rd != NULL)
	{
		if (rd->kind == REDIR_HEREDOC)
		{
			unlink(rd->file);
			free(rd->file);
		}
		rd = rd->next;
	}
}

static void	child_exec_external(t_cmd *cmd, t_minishell *sh, char *path)
{
	char		**envp;
	struct stat	st;

	envp = env_list_to(sh->env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirections(cmd, sh) != 0)
		exit(1);
	execve(path, cmd->argv, envp);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		pex_print(cmd->argv[0], "is a directory");
		clean_child(path, envp, cmd);
		exit(126);
	}
	perror(cmd->argv[0]);
	clean_child(path, envp, cmd);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

int	execute_external_command(t_cmd *cmd, t_minishell *sh)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (cmd->argv[0][0] == '\0')
		return (0);
	path = get_cmd_path(cmd->argv[0], sh);
	if (path == NULL)
		return (pex_cmd_error(cmd->argv[0]), 127);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (pex_perror("fork"), free(path), 1);
	if (pid == 0)
		child_exec_external(cmd, sh, path);
	free(path);
	waitpid(pid, &status, 0);
	set_signal_handlers();
	if (WIFEXITED(status))
		sh->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->last_status = 128 + WTERMSIG(status);
	return (sh->last_status);
}
