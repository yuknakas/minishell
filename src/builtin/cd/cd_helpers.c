/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:45:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/16 12:51:48 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	cd_get_home_path(t_minishell *sh, const char **out_path)
{
	t_envp	*home;

	home = find_env_node(sh->env, "HOME");
	if (home && home->value)
	{
		*out_path = home->value;
		return (0);
	}
	*out_path = getenv("HOME");
	if (*out_path)
		return (0);
	return (1);
}

int	cd_get_oldpwd(t_minishell *sh, const char **out_path)
{
	t_envp	*old;

	old = find_env_node(sh->env, "OLDPWD");
	if (!old || !old->value)
		return (1);
	*out_path = old->value;
	return (0);
}
