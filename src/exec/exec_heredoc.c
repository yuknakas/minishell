/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:06:41 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/21 14:10:46 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	write_heredoc_line(char *line, int fd, t_redir *r,
//		t_minishell *sh)
// {
// 	char	*expanded;

// 	if (!r->no_expand)
// 	{
// 		expanded = expand_vars_simple(line, sh);
// 		if (expanded)
// 		{
// 			write(fd, expanded, ft_strlen(expanded));
// 			free(expanded);
// 		}
// 		else
// 			write(fd, line, ft_strlen(line));
// 	}
// 	else
// 		write(fd, line, ft_strlen(line));
// 	write(fd, "\n", 1);
// }

// static void	heredoc_readline_loop(int fd, t_redir *redir, t_minishell *sh)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (g_sig)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (line == NULL || ft_strcmp(line, redir->file) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write_heredoc_line(line, fd, redir, sh);
// 		free(line);
// 	}
// }

// static char	*heredoc_name(t_cmd *cmd)
// {
// 	char	*cmd_nb;
// 	char	*name;
// 	char	*nb_xx;

// 	cmd_nb = ft_itoa(cmd->cmd_no);
// 	nb_xx = ft_strjoin(cmd_nb, "_XXXXXX");
// 	name = ft_strjoin("/tmp/minishell_heredoc_", nb_xx);
// 	free(cmd_nb);
// 	free(nb_xx);
// 	return (name);
// }

// int	handle_heredoc(t_cmd *cmd, t_redir *redir, t_minishell *sh)
// {
// 	int		fd;
// 	char	*tmp_file;

// 	tmp_file = ft_strdup(heredoc_name(cmd));
// 	if (tmp_file == NULL)
// 		return (-1);
// 	fd = mkstemp(tmp_file);
// 	if (fd == -1)
// 		return (free(tmp_file), -2);
// 	heredoc_readline_loop(fd, redir, sh);
// 	close(fd);
// 	fd = open(tmp_file, O_RDONLY);
// 	free(redir->file);
// 	redir->file = tmp_file;
// 	return (fd);
// }

// This handler is for the dedicated heredoc child process.
// It simply exits the child, which the parent will detect.
static void	heredoc_child_sigint(int sig)
{
	(void)sig;
	exit(130);
}

static void	write_heredoc_line(char *line, int fd, t_redir *r, t_minishell *sh)
{
	char	*expanded;

	if (!r->no_expand)
	{
		expanded = expand_vars_simple(line, sh);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
		else
			write(fd, line, ft_strlen(line));
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

// This function now runs inside a dedicated child process.
static void	heredoc_read_loop(int fd, t_redir *redir, t_minishell *sh)
{
	char	*line;

	signal(SIGINT, heredoc_child_sigint);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			exit(0);
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			exit(0);
		}
		write_heredoc_line(line, fd, redir, sh);
		free(line);
	}
}

// This function is a placeholder for your existing heredoc_name logic
static char	*heredoc_name(t_cmd *cmd)
{
	char	*cmd_nb;
	char	*name;
	char	*nb_xx;

	cmd_nb = ft_itoa(cmd->cmd_no);
	nb_xx = ft_strjoin(cmd_nb, "_XXXXXX");
	name = ft_strjoin("/tmp/minishell_heredoc_", nb_xx);
	free(cmd_nb);
	free(nb_xx);
	return (name);
}

int	handle_heredoc(t_cmd *cmd, t_redir *redir, t_minishell *sh)
{
	int		fd;
	char	*tmp_file;
	pid_t	pid;
	int		status;

	tmp_file = heredoc_name(cmd);
	if (!tmp_file)
		return (-1);
	fd = mkstemp(tmp_file);
	if (fd == -1)
		return (free(tmp_file), -2);
	pid = fork();
	if (pid == -1)
		return (close(fd), free(tmp_file), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		heredoc_read_loop(fd, redir, sh);
		close(fd);
		exit(0);
	}
	close(fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	set_signal_handlers();
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		unlink(tmp_file);
		free(tmp_file);
		free(redir->file);
		redir->file = NULL;
		write(STDOUT_FILENO, "\n", 1);
		sh->last_status = 130;
		return (-1);
	}
	fd = open(tmp_file, O_RDONLY);
	free(redir->file);
	redir->file = tmp_file;
	return (fd);
}
