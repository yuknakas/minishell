/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:04:12 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:04:13 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	unclosed_quote_error(char qt_type)
{
	if (qt_type == '\'')
		ft_putstr_fd("minishell: unclosed single quote\n", 2);
	else if (qt_type == '"')
		ft_putstr_fd("minishell: unclosed double quote\n", 2);
	return (1);
}

int	take_quote(char *line, int *i)
{
	int		j;
	char	quote;

	j = 1;
	quote = *line;
	while (line[j])
	{
		if (line[j] == '\\' && quote == '"' && line[j + 1] != '\0')
			j += 2;
		else if (line[j] == quote)
			break ;
		else
			j++;
	}
	if (line[j] == '\0')
		return (unclosed_quote_error(quote));
	*i += j + 1;
	return (0);
}
