/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:06:47 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:13:30 by raosmona         ###   ########.fr       */
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
	if (handle_redirections(cmd, sh) != 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
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

static void	child_exec_external(t_cmd *cmd, t_minishell *sh, char *path)
{
	char	**envp;

	envp = env_list_to(sh->env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirections(cmd, sh) != 0)
		exit(1);
	if (execve(path, cmd->argv, envp) == -1)
	{
		pex_cmd_error(cmd->argv[0]);
		free(path);
		_freearr(envp);
		exit(126);
	}
}

int	execute_external_command(t_cmd *cmd, t_minishell *sh)
{
	char	*path;
	pid_t	pid;
	int		status;

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
