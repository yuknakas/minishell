/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iskey.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:40:36 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/18 10:26:39 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	_unclosed_qt(char qt_type);

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_word_start(char c)
{
	return (c && !is_blank(c));
}


int	take_quote(char *line, int *i)
{
	int	j;
	char	quote;

	j = 1;
	quote = *line;
	while(line[j] != quote)
	{
		if (line[j] == '\0')
			return (_unclosed_qt(quote));
		j++;
	}
	*i += j + 1;
	return (0);
}

int	_unclosed_qt(char qt_type)
{
	if (qt_type == '\'')
		printf("> unclosed single quote: error, process terminated\n");
	else if (qt_type == '"')
		printf("> unclosed double quote: error, process terminated\n");
	return (1);
}
