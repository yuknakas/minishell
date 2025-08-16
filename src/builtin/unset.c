/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:40:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/16 12:22:34 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_unset(char **args, t_minishell *sh)
{
	int		i;
	char	*key;

	i = 1;
	while (args[i])
	{
		key = args[i];
		if (!is_valid_env_key(key))
		{
			pex_print_arg("unset", key, "not a valid identifier");
			return (1);
		}
		remove_env(&sh->env, key);
		i++;
	}
	return (0);
}
