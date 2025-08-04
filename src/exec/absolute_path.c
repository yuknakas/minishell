/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:51:45 by yuknakas          #+#    #+#             */
/*   Updated: 2025/08/04 13:57:53 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			execute(char *cmd, t_minishell *sh);
static int	absolute_path(char *cmd, t_minishell *sh);
char		**_set_cmd(char *command);

int	execute(char *cmd, t_minishell *sh)
{
	if (cmd == NULL || *cmd == '\0')
	{
		pex_putstr_int("bash: permission denied\n");
		return (0);
	}
	if (*cmd == '/')
		return (absolute_path(cmd, sh));
	return (find_path(cmd, sh));
}

static int	absolute_path(char *cmd, t_minishell *sh)
{
	char	**cmd_arr;
	int		sucess;
	char	**envp;

	envp = env_list_to(sh->env);
	cmd_arr = _set_cmd(cmd);
	if (access(cmd_arr[0], F_OK | X_OK))
	{
		pex_cmd_error(cmd);
		return (127);
	}
	sucess = execve(cmd_arr[0], cmd_arr, envp);
	_freearr(cmd_arr);
	return (sucess);
}

char	**_set_cmd(char *command)
{
	char	**cmd_arg;

	if (command == NULL || *command == '\0')
	{
		pex_putstr_int("bash: permission denied\n");
		return (NULL);
	}
	cmd_arg = ft_split(command, ' ');
	if (cmd_arg == NULL)
	{
		pex_putstr_int("Error: memory allocation failed\n");
		return (NULL);
	}
	return (cmd_arg);
}
