/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:05:23 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:05:24 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	process_character(char **new, const char *word, int *i,
		t_minishell *sh)
{
	t_exp_state	state;

	state.in_squote = 0;
	state.in_dquote = 0;
	while (word[*i])
	{
		if (word[*i] == '\'' || word[*i] == '"')
		{
			handle_quotes(word[*i], &state);
			(*i)++;
		}
		else if (word[*i] == '$' && !state.in_squote)
			handle_dollar(new, word, i, sh);
		else if (word[*i] == '\\' && !state.in_squote)
			handle_escape(new, word, i, &state);
		else
		{
			append_char_to_str(new, word[*i]);
			(*i)++;
		}
	}
}

/*
** Expands a token word, handling variables ($VAR), single quotes (''),
** double quotes (""), and escapes (\) according to shell rules.
*/
char	*expand_token_word(char *word, t_minishell *sh)
{
	char	*expanded_word;
	int		i;

	expanded_word = ft_strdup("");
	if (!expanded_word)
		return (NULL);
	i = 0;
	process_character(&expanded_word, word, &i, sh);
	return (expanded_word);
}
