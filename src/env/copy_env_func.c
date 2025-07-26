/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <razakosmonaliev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:16:35 by raosmona          #+#    #+#             */
/*   Updated: 2025/07/26 15:17:31 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_envp(t_envp *env)
{
	t_envp	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	print_envp(t_envp *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

t_envp	*copy_envp(char **envp)
{
	t_envp	*head;
	t_envp	*curr;
	int		i;
	char	*eq;
	t_envp	*node;

	head = NULL;
	curr = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			node = malloc(sizeof(t_envp));
			node->key = ft_substr(envp[i], 0, eq - envp[i]);
			node->value = ft_strdup(eq + 1);
			node->next = NULL;
			if (!head)
				head = node;
			else
				curr->next = node;
			curr = node;
		}
		i++;
	}
	return (head);
}
