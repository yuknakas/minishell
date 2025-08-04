/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:16:35 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/04 14:08:22 by raosmona         ###   ########.fr       */
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

static t_envp	*create_env_node(char *env_str)
{
	char	*eq;
	t_envp	*node;

	eq = ft_strchr(env_str, '=');
	if (!eq)
		return (NULL);
	node = malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->key = ft_substr(env_str, 0, eq - env_str);
	node->value = ft_strdup(eq + 1);
	node->next = NULL;
	return (node);
}

t_envp	*copy_envp(char **envp)
{
	t_envp	*head;
	t_envp	*curr;
	int		i;
	t_envp	*node;

	head = NULL;
	curr = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (node)
		{
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
