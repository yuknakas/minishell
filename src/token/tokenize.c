/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:15:25 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/18 10:29:38 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		word_token(char **line, t_token **token_list);

t_token	*make_token_list(char *line)
{
	t_token	*token_list;

	token_list = NULL;
	if (line == NULL)
		return (NULL);
	while (*line)
	{
		if (is_blank(*line))
			line++;
		else if (is_word_start(*line))
		{
			if (word_token(&line, &token_list))
				return (NULL);
		}
		else
			line++;
	}
	return (token_list);
}

int	word_token(char **line, t_token **token_list)
{
	char	*token_line;
	int		i;

	if (*line == NULL || **line == '\0')
		return (1);
	i = 0;
	while (line[0][i] != '\0' && !is_blank(line[0][i]))
	{
		if (line[0][i] == '\'' || line[0][i] == '"')
		{
			if (take_quote(&line[0][i], &i))
				return (1);
			else
				continue ;
		}
		i++;
	}
	token_line = ft_strndup(*line, i);
	if (append_token(token_list, new_token(token_line)))
		return (1);
	*line += i;
	return (0);
}
