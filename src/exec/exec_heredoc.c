/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:06:41 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:06:42 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	heredoc_readline_loop(int fd, t_redir *redir, t_minishell *sh)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(line, fd, redir, sh);
		free(line);
	}
}

int	handle_heredoc(t_redir *redir, t_minishell *sh)
{
	int		fd;
	char	*tmp_file;

	tmp_file = ft_strdup("/tmp/minishell_heredoc_XXXXXX");
	if (tmp_file == NULL)
		return (-1);
	fd = mkstemp(tmp_file);
	if (fd == -1)
		return (free(tmp_file), -1);
	heredoc_readline_loop(fd, redir, sh);
	close(fd);
	fd = open(tmp_file, O_RDONLY);
	unlink(tmp_file);
	free(tmp_file);
	return (fd);
}
