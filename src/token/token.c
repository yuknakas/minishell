/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:04:02 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/19 15:50:03 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	process_line(char **line, t_token **token_list)
{
	while (**line)
	{
		if (is_blank(**line))
			(*line)++;
		else if (is_operator(*line))
		{
			if (operator_token(line, token_list))
				return (1);
		}
		else
		{
			if (word_token(line, token_list))
				return (1);
		}
	}
	return (0);
}

t_token	*make_token_list(char *line)
{
	t_token	*token_list;

	token_list = NULL;
	if (line == NULL)
		return (NULL);
	if (process_line(&line, &token_list))
	{
		free_token_list(token_list);
		return (NULL);
	}
	return (token_list);
}
