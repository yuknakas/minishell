/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:51:45 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/26 16:03:12 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			execute(char *cmd, char **envp);
static int	absolute_path(char *cmd, char **envp);
char		**_set_cmd(char *command);

int	execute(char *cmd, char **envp)
{
	if (cmd == NULL || *cmd == '\0')
	{
		pex_putstr_int("bash: permission denied\n");
		return (0);
	}
	if (*cmd == '/')
		return (absolute_path(cmd, envp));
	return (find_path(cmd, envp));
}

static int	absolute_path(char *cmd, char **envp)
{
	char	**cmd_arr;
	int		sucess;

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

	// int		i;
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
	// i = 0;
	return (cmd_arg);
}
