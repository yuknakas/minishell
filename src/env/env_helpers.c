/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:15:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/16 15:40:13 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**allocate_env_array(int size);
static int	populate_env_array(t_envp *env, char **arr);
static int	allocate_env_entry(char **dest, const char *key, const char *val,
				int len);

int	env_list_size(t_envp *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**env_list_to(t_envp *env)
{
	int		size;
	char	**arr;

	size = env_list_size(env);
	arr = allocate_env_array(size);
	if (!arr)
		return (NULL);
	if (populate_env_array(env, arr) != 0)
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

static char	**allocate_env_array(int size)
{
	char	**arr;

	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	return (arr);
}

static int	populate_env_array(t_envp *env, char **arr)
{
	int			i;
	int			len;
	const char	*val;
	t_envp		*cur;

	i = 0;
	cur = env;
	while (cur)
	{
		if (cur->value != NULL)
		{
			val = cur->value;
			len = ft_strlen(cur->key) + ft_strlen(val) + 2;
			if (allocate_env_entry(&arr[i], cur->key, val, len) != 0)
			{
				free_env_array_on_fail(arr, i);
				return (-1);
			}
			i++;
		}
		cur = cur->next;
	}
	arr[i] = NULL;
	return (0);
}

static int	allocate_env_entry(char **dest, const char *key, const char *val,
		int len)
{
	*dest = malloc(sizeof(char) * len);
	if (!*dest)
		return (-1);
	ft_strlcpy(*dest, key, len);
	ft_strlcat(*dest, "=", len);
	ft_strlcat(*dest, val, len);
	return (0);
}
