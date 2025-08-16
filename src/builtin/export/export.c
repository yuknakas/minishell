/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:10:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/16 15:02:08 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void		print_export_sorted(t_minishell *sh);

static void	free_kv(char *k, char *v)
{
	if (k)
		free(k);
	if (v)
		free(v);
}

static int	process_export_arg(char *arg, t_minishell *sh)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign != NULL)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (!is_valid_env_key(key))
	{
		pex_print_arg("export", key, "not a valid identifier");
		free_kv(key, value);
		return (1);
	}
	add_or_update_env(&sh->env, key, value);
	free_kv(key, value);
	return (0);
}

int	builtin_export(char **args, t_minishell *sh)
{
	int	i;

	if (args[1] == NULL)
	{
		print_export_sorted(sh);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], sh))
			return (1);
		i++;
	}
	return (0);
}
