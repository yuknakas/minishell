/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:49:04 by yuknakas          #+#    #+#             */
/*   Updated: 2025/08/16 15:47:43 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static char	*get_cmd_path_from_pathvar(const char *command,
// 		const char *env_path)
// {
// 	char	**path_comp;
// 	char	*new_path;
// 	char	*path;
// 	int		i;

// 	if (env_path == NULL)
// 		return (NULL);
// 	path_comp = ft_split(env_path, ':');
// 	if (path_comp == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (path_comp[i] != NULL)
// 	{
// 		new_path = ft_strjoin(path_comp[i], "/");
// 		path = ft_strjoin(new_path, command);
// 		free(new_path);
// 		if (access(path, F_OK | X_OK) == 0)
// 		{
// 			_freearr(path_comp);
// 			return (path);
// 		}
// 		free(path);
// 		i++;
// 	}
// 	_freearr(path_comp);
// 	return (NULL);
// }

// char	*get_cmd_path(char *command, t_minishell *sh)
// {
// 	char	*env_path;
// 	t_envp	*node;

// 	if (command == NULL || command[0] == '\0')
// 		return (NULL);
// 	if (ft_strchr(command, '/'))
// 	{
// 		if (access(command, F_OK | X_OK) == 0)
// 			return (ft_strdup(command));
// 		return (NULL);
// 	}
// 	node = find_env_node(sh->env, "PATH");
// 	env_path = (node && node->value) ? node->value : NULL;
// 	return (get_cmd_path_from_pathvar(command, env_path));
// }

static char	*build_and_check_path(const char *dir, const char *command)
{
	char	*new_path;
	char	*path;

	new_path = ft_strjoin(dir, "/");
	if (!new_path)
		return (NULL);
	path = ft_strjoin(new_path, command);
	free(new_path);
	if (!path)
		return (NULL);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

static char	*search_in_path(const char *command, char **path_comp)
{
	int		i;
	char	*path;

	i = 0;
	while (path_comp[i] != NULL)
	{
		path = build_and_check_path(path_comp[i], command);
		if (path != NULL)
		{
			_freearr(path_comp);
			return (path);
		}
		i++;
	}
	_freearr(path_comp);
	return (NULL);
}

static char	*get_cmd_path_from_pathvar(const char *command,
		const char *env_path)
{
	char	**path_comp;

	if (env_path == NULL)
		return (NULL);
	path_comp = ft_split(env_path, ':');
	if (path_comp == NULL)
		return (NULL);
	return (search_in_path(command, path_comp));
}

char	*get_cmd_path(char *command, t_minishell *sh)
{
	char	*env_path;
	t_envp	*node;

	if (command == NULL || command[0] == '\0')
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	node = find_env_node(sh->env, "PATH");
	if (node && node->value)
		env_path = node->value;
	else
		env_path = NULL;
	return (get_cmd_path_from_pathvar(command, env_path));
}

int	find_path(char *command, t_minishell *sh)
{
	char	**cmd;
	char	*path;
	int		sucess;
	char	**envp;

	envp = env_list_to(sh->env);
	cmd = _set_cmd(command);
	if (cmd == NULL)
		return (-1);
	path = get_cmd_path(cmd[0], sh);
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
