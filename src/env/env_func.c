/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:32:41 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/04 13:57:36 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int		i;
	int		len;

	size = env_list_size(env);
	arr = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (env)
	{
		len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
		arr[i] = malloc(sizeof(char) * len);
		ft_strlcpy(arr[i], env->key, len);
		ft_strlcat(arr[i], "=", len);
		ft_strlcat(arr[i], env->value, len);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
