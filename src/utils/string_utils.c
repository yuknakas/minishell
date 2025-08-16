/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:58:03 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 17:58:05 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	process_string(const char *word, char *out, int *j)
{
	int		i;
	char	quote_char;

	i = 0;
	quote_char = 0;
	while (word[i])
	{
		if ((word[i] == '\'' || word[i] == '"') && quote_char == 0)
			quote_char = word[i];
		else if (word[i] == quote_char)
			quote_char = 0;
		else
		{
			out[*j] = word[i];
			(*j)++;
		}
		i++;
	}
}

char	*remove_quotes(const char *word)
{
	char	*out;
	int		j;

	if (!word)
		return (NULL);
	out = malloc(ft_strlen(word) + 1);
	if (!out)
		return (NULL);
	j = 0;
	process_string(word, out, &j);
	out[j] = '\0';
	return (out);
}
