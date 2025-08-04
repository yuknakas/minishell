/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:29:15 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/18 10:10:40 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *token_line)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		printf("error with memory allocation\n");
		return (NULL);
	}
	new_token->line = token_line;
	new_token->next = NULL;
	new_token->is_expanded = 0;
	new_token->type = TOKEN_WORD;
	return (new_token);
}

int	append_token(t_token **token_list, t_token *new_token)
{
	t_token	*last_token;

	if (*token_list == NULL)
	{
		*token_list = new_token;
		return (0);
	}
	last_token = ft_last_token(*token_list);
	if (last_token == NULL)
		return (1);
	last_token->next = new_token;
	return (0);
}

t_token	*ft_last_token(t_token *token_list)
{
	if (token_list == NULL)
		return (NULL);
	while (token_list->next != NULL)
		token_list = token_list->next;
	return (token_list);
}
