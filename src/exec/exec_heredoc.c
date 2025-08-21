/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:06:41 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/21 15:31:50 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int	_cont_handle(char *tmp_f, pid_t pid, t_redir *rd, t_minishell *sh)
{
	int	fd;
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	set_signal_handlers();
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		unlink(tmp_f);
		free(tmp_f);
		free(rd->file);
		rd->file = NULL;
		write(STDOUT_FILENO, "\n", 1);
		sh->last_status = 130;
		return (-1);
	}
	fd = open(tmp_f, O_RDONLY);
	free(rd->file);
	rd->file = tmp_f;
	return (fd);
}

int	handle_heredoc(t_cmd *cmd, t_redir *redir, t_minishell *sh)
{
	int		fd;
	char	*tmp_file;
	pid_t	pid;

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
	return (_cont_handle(tmp_file, pid, redir, sh));
}
