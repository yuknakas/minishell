/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:29:15 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/15 15:40:09 by yuknakas         ###   ########.fr       */
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
	return (new_token);
}

void	append_token(t_token *last_token, t_token *new_token)
{
	if (last_token == NULL || new_token == NULL)
		return ;
	last_token->next = new_token;
	return ;
}


