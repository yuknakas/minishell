/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_resolve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:50:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/16 12:51:15 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	resolve_no_arg(const char **out_path, char **out_old_pwd,
		t_minishell *sh)
{
	*out_old_pwd = getcwd(NULL, 0);
	if (cd_get_home_path(sh, out_path))
	{
		pex_print("cd", "HOME not set");
		free(*out_old_pwd);
		*out_old_pwd = NULL;
		return (1);
	}
	return (0);
}

static int	resolve_dash_arg(const char **out_path, char **out_old_pwd,
		t_minishell *sh)
{
	*out_old_pwd = getcwd(NULL, 0);
	if (cd_get_oldpwd(sh, out_path))
	{
		pex_print("cd", "OLDPWD not set");
		free(*out_old_pwd);
		*out_old_pwd = NULL;
		return (1);
	}
	ft_putendl_fd((char *)*out_path, STDOUT_FILENO);
	return (0);
}

int	resolve_cd_path(char **args, t_minishell *sh, const char **out_path,
		char **out_old_pwd)
{
	if (args[1] == NULL)
		return (resolve_no_arg(out_path, out_old_pwd, sh));
	if (ft_strcmp(args[1], "-") == 0)
		return (resolve_dash_arg(out_path, out_old_pwd, sh));
	*out_old_pwd = getcwd(NULL, 0);
	*out_path = args[1];
	return (0);
}
