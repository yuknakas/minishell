/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:40:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/16 12:51:23 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	update_pwd_vars(t_minishell *sh, const char *old_pwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	if (old_pwd)
		add_or_update_env(&sh->env, "OLDPWD", old_pwd);
	add_or_update_env(&sh->env, "PWD", cwd);
	free(cwd);
}

static int	do_chdir_and_update(const char *path, char *old_pwd,
		t_minishell *sh)
{
	if (chdir(path) != 0)
	{
		pex_perror("cd");
		free(old_pwd);
		return (1);
	}
	update_pwd_vars(sh, old_pwd);
	free(old_pwd);
	return (0);
}

int	builtin_cd(char **args, t_minishell *sh)
{
	const char	*path;
	char		*old_pwd;

	old_pwd = NULL;
	if (resolve_cd_path(args, sh, &path, &old_pwd))
		return (1);
	return (do_chdir_and_update(path, old_pwd, sh));
}
