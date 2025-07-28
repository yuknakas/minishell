/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:32:41 by razakosmona       #+#    #+#             */
/*   Updated: 2025/07/28 20:36:09 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int env_list_size(t_envp *env)
{
    int size = 0;
    while (env)
    {
        size++;
        env = env->next;
    }
    return size;
}

char	**env_list_to(t_envp *env)
{
    int size = env_list_size(env);
    char **arr = malloc(sizeof(char *) * (size + 1));
    int i = 0;
    while (env)
    {
        int len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
        arr[i] = malloc(sizeof(char) * len);
        ft_strlcpy(arr[i], env->key, len);
        ft_strlcat(arr[i], "=", len);
        ft_strlcat(arr[i], env->value, len);
        env = env->next;
        i++;
    }
    arr[i] = NULL;
    return arr;
}
