/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:03:42 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/21 13:28:35 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

// static int	do_heredoc(t_cmd *cmds, t_minishell *sh)
// {
// 	t_redir	*rd;
// 	int		result;

// 	result = -100;
// 	while (cmds != NULL)
// 	{
// 		rd = cmds->rd;
// 		while (rd != NULL)
// 		{
// 			if (rd->kind == REDIR_HEREDOC)
// 				result = handle_heredoc(cmds, rd, sh);
// 			rd = rd->next;
// 		}
// 		cmds = cmds->next;
// 	}
// 	return (1);
// }

// static void	process_line_part(char *part, t_minishell *sh)
// {
// 	sh->tokens = make_token_list(part);
// 	if (!sh->tokens)
// 	{
// 		sh->last_status = 0;
// 		return ;
// 	}
// 	sh->cmds = parse(sh->tokens, sh);
// 	if (!sh->cmds)
// 	{
// 		free_token_list(sh->tokens);
// 		return ;
// 	}
// 	do_heredoc(sh->cmds, sh);
// 	sh->last_status = execute_pipeline(sh->cmds, sh);
// 	free_token_list(sh->tokens);
// 	free_cmd_list(sh->cmds);
// }

// void	shell_loop(t_minishell *sh)
// {
// 	char	*line;
// 	char	**parts;
// 	int		i;

// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 			break ;
// 		add_history(line);
// 		parts = split_unquoted_semicolons(line);
// 		free(line);
// 		if (!parts)
// 			continue ;
// 		i = 0;
// 		while (parts[i])
// 		{
// 			process_line_part(parts[i], sh);
// 			i++;
// 		}
// 		_freearr(parts);
// 	}
// }

static int	do_heredoc(t_cmd *cmds, t_minishell *sh)
{
	t_redir	*rd;
	int		result;

	result = -100;
	while (cmds != NULL)
	{
		rd = cmds->rd;
		while (rd != NULL)
		{
			if (rd->kind == REDIR_HEREDOC)
			{
				if (handle_heredoc(cmds, rd, sh) == -1)
					return (-1);
			}
			rd = rd->next;
		}
		cmds = cmds->next;
	}
	return (1);
}

static void	process_line_part(char *part, t_minishell *sh)
{
	sh->tokens = make_token_list(part);
	if (!sh->tokens)
	{
		sh->last_status = 0;
		return ;
	}
	sh->cmds = parse(sh->tokens, sh);
	if (!sh->cmds)
	{
		free_token_list(sh->tokens);
		return ;
	}
	if (do_heredoc(sh->cmds, sh) == -1)
	{
		free_token_list(sh->tokens);
		free_cmd_list(sh->cmds);
		return ;
	}
	sh->last_status = execute_pipeline(sh->cmds, sh);
	free_token_list(sh->tokens);
	free_cmd_list(sh->cmds);
}

void	shell_loop(t_minishell *sh)
{
	char	*line;
	char	**parts;
	int		i;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		parts = split_unquoted_semicolons(line);
		free(line);
		if (!parts)
			continue ;
		i = 0;
		while (parts[i])
		{
			process_line_part(parts[i], sh);
			i++;
		}
		_freearr(parts);
	}
}
