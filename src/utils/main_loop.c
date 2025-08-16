/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:03:42 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:03:43 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	process_line_part(char *part, t_minishell *sh)
{
	sh->tokens = make_token_list(part);
	if (!sh->tokens)
	{
		sh->last_status = 258;
		return ;
	}
	sh->cmds = parse(sh->tokens, sh);
	if (!sh->cmds)
	{
		free_token_list(sh->tokens);
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
