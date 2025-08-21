/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:03:42 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/21 15:29:55 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

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
				result = handle_heredoc(cmds, rd, sh);
				if (result == -1)
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
		return (free_token_list(sh->tokens));
	if (do_heredoc(sh->cmds, sh) == -1)
	{
		free_token_list(sh->tokens);
		free_cmd_list(sh->cmds);
		return ;
	}
	if (sh->cmds)
	{
		signal(SIGINT, SIG_IGN);
		sh->last_status = execute_pipeline(sh->cmds, sh);
		set_signal_handlers();
	}
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
		if (g_sig == SIGINT)
		{
			sh->last_status = 130;
			g_sig = 0;
		}
		if (!line)
			break ;
		add_history(line);
		parts = split_unquoted_semicolons(line);
		free(line);
		if (!parts)
			continue ;
		i = 0;
		while (parts[i])
			process_line_part(parts[i++], sh);
		_freearr(parts);
	}
}
