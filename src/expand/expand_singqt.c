/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_singqt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:31:06 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/18 17:00:01 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*exp_sengqt(char *line);

void	expand_singqt_node(t_node *node)
{
	t_token	*tok;

	if (node == NULL)
		return ;
	tok = node->arg_list;
	while (tok != NULL)
	{
		tok->line = exp_sengqt(tok->line);
		tok = tok->next;
	}
	return (exp_sengqt(node->next));
}

char	*exp_sengqt(char *line)
{
	char	*new_line;
	size_t	i;

	new_line = malloc(1);
	if (new_line == NULL)
		return (NULL);
	new_line[0] = '\0';
	i = 1; // skip \'
	while (line[i])
	{
		if (line[i] != '\'')
			new_line = append_char(new_line, line[i]);
		i++;
	}
	free(line);
	return (new_line);
}