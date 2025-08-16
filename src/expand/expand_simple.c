/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:05:30 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:05:31 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	perform_expansion(char **new, const char *word, int *i,
		t_minishell *sh)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	(*i)++;
	var_name = get_var_name(&word[*i]);
	if (var_name[0] == '\0')
	{
		append_char_to_str(new, '$');
		free(var_name);
		return ;
	}
	var_value = lookup_var_value(var_name, sh);
	tmp = *new;
	*new = ft_strjoin(tmp, var_value);
	free(tmp);
	*i += (int)ft_strlen(var_name);
	free(var_name);
	free(var_value);
}

/*
** Expands variables ($VAR) in a string without considering quotes.
** Used primarily for heredoc content.
*/
char	*expand_vars_simple(const char *word, t_minishell *sh)
{
	char	*expanded_word;
	int		i;

	expanded_word = ft_strdup("");
	if (!expanded_word)
		return (NULL);
	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
			perform_expansion(&expanded_word, word, &i, sh);
		else
		{
			append_char_to_str(&expanded_word, word[i]);
			i++;
		}
	}
	return (expanded_word);
}
