/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:49:04 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/26 15:58:09 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			find_path(char *command, char **envp);
static char	*_pathway(char *command);
static char	*_check_path(char **path_comp, char *command);

int	find_path(char *command, char **envp)
{
	char	**cmd;
	char	*path;
	int		sucess;

	cmd = _set_cmd(command);
	if (cmd == NULL)
		return (-1);
	path = _pathway(cmd[0]);
	if (path == NULL)
	{
		pex_cmd_error(cmd[0]);
		_freearr(cmd);
		return (127);
	}
	sucess = execve(path, cmd, envp);
	free(path);
	_freearr(cmd);
	if (sucess == -1)
		return (pex_putstr_int("Error: Failed Execution\n"));
	return (sucess);
}

static char	*_pathway(char *command)
{
	char	*env_path;
	char	**path_comp;

	// int		i;
	// i = 0;
	env_path = getenv("PATH");
	path_comp = ft_split(env_path, ':');
	if (path_comp == NULL)
	{
		pex_putstr_int("Error: Split Failed\n");
		return (NULL);
	}
	return (_check_path(path_comp, command));
}

static char	*_check_path(char **path_comp, char *command)
{
	char	*new_path;
	char	*path;
	int		i;

	i = 0;
	while (path_comp[i] != NULL)
	{
		new_path = ft_strjoin(path_comp[i], "/");
		path = ft_strjoin(new_path, command);
		free(new_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			_freearr(path_comp);
			return (path);
		}
		free(path);
		i++;
	}
	_freearr(path_comp);
	return (NULL);
}
