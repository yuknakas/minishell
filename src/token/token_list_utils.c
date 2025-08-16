/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:04:25 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:04:26 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *token_line)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->line = token_line;
	new->next = NULL;
	new->is_expanded = 0;
	new->type = TOKEN_WORD;
	return (new);
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
