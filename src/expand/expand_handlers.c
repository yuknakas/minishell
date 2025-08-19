/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:05:36 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/19 14:20:27 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Toggles the quote state based on the character encountered.
*/
void	handle_quotes(char c, t_exp_state *state, int *i)
{
	if (c == '\'' && !state->in_dquote)
	{
		state->in_squote = !state->in_squote;
		(*i)++;
	}
	else if (c == '"' && !state->in_squote)
	{
		state->in_dquote = !state->in_dquote;
		(*i)++;
	}
}

/*
** Handles the expansion of a variable when a '$' is found.
*/
void	handle_dollar(char **new_word, const char *word, int *i,
		t_minishell *sh)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	(*i)++;
	var_name = get_var_name(&word[*i]);
	if (var_name[0] == '\0')
	{
		append_char_to_str(new_word, '$');
		free(var_name);
		return ;
	}
	var_value = lookup_var_value(var_name, sh);
	tmp = *new_word;
	*new_word = ft_strjoin(tmp, var_value);
	free(tmp);
	*i += (int)ft_strlen(var_name);
	free(var_name);
	free(var_value);
}

/*
** Handles backslash escapes. In double quotes, only \, ", and $ are escaped.
** Outside quotes, the backslash is removed, and the next char is literal.
*/
void	handle_escape(char **new_word, const char *word, int *i,
		t_exp_state *state)
{
	(*i)++;
	if (word[*i] == '\0')
	{
		append_char_to_str(new_word, '\\');
		return ;
	}
	if (state->in_dquote)
	{
		if (word[*i] == '\\' || word[*i] == '"' || word[*i] == '$')
			append_char_to_str(new_word, word[*i]);
		else
		{
			append_char_to_str(new_word, '\\');
			append_char_to_str(new_word, word[*i]);
		}
	}
	else
		append_char_to_str(new_word, word[*i]);
	(*i)++;
}
