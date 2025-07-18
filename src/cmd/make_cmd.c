/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:19:21 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/18 16:36:16 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*parse_tokens(t_token *tok_list)
{
	t_node	node;
	t_node	*node_list;

	node_list = &node;
	node_list->next = new_node();
	while (tok_list != NULL)
	{
		if (tok_list->type == TOKEN_WORD)
			word_token(last_node(node_list), tok_list);
		else
			return (NULL); // need to add
		tok_list = tok_list->next;
	}
	return (node.next);
}

t_node	*new_node(void)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->arg_list = NULL;
	new->next = NULL;
	return (new);
}

void	word_token(t_node *node, t_token *token)
{
	int	i;
	t_token	*list;

	if (node->arg_list == NULL)
	{
		node->arg_list = clone_token(token);
		return ;
	}
	list = node->arg_list;
	while (list->next != NULL)
		list = list->next;
	list->next = clone_token(token);
	return ;
}

t_token	*clone_token(t_token *src)
{
	return (new_token(src->line));
}
