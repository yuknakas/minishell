/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:06:12 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/19 14:53:44 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_redir_file(t_redir *redir, t_minishell *sh)
{
	int	fd;
	
	sh = NULL;
	if (redir->kind == REDIR_IN || redir->kind == REDIR_HEREDOC)
		fd = open(redir->file, O_RDONLY);
	else if (redir->kind == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->kind == REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

int	handle_redirections(t_cmd *cmd, t_minishell *sh)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->rd;
	while (redir != NULL)
	{
		fd = open_redir_file(redir, sh);
		if (fd == -1)
			return (pex_file_error(redir->file), 1);
		if (redir->kind == REDIR_IN || redir->kind == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (0);
}
