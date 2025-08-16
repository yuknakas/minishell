/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:05:16 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:05:17 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Appends a single character to a dynamically allocated string.
*/
void	append_char_to_str(char **str, char c)
{
	char	buf[2];
	char	*tmp;

	if (!str)
		return ;
	buf[0] = c;
	buf[1] = '\0';
	tmp = *str;
	*str = ft_strjoin(tmp, buf);
	free(tmp);
}

/*
** Extracts a valid environment variable name from a string.
*/
char	*get_var_name(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (ft_substr(str, 0, i));
}

/*
** Looks up the value of an environment variable. Returns an empty string if
** not found.
*/
char	*lookup_var_value(const char *var_name, t_minishell *sh)
{
	t_envp	*node;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(sh->last_status));
	node = find_env_node(sh->env, var_name);
	if (node)
	{
		if (node->value)
			return (ft_strdup(node->value));
		return (ft_strdup(""));
	}
	return (ft_strdup(""));
}
