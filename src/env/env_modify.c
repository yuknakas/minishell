/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:25:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/21 15:31:37 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_existing_env(t_envp *node, const char *value)
{
	free(node->value);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	return (0);
}

static t_envp	*create_new_env_node(const char *key, const char *value)
{
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

static void	append_env_node(t_envp **head, t_envp *node)
{
	t_envp	*cur;

	if (*head == NULL)
		*head = node;
	else
	{
		cur = *head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = node;
	}
}

int	add_or_update_env(t_envp **head, const char *key, const char *value)
{
	t_envp	*node;

	node = find_env_node(*head, key);
	if (node != NULL)
		return (update_existing_env(node, value));
	node = create_new_env_node(key, value);
	if (!node)
		return (1);
	append_env_node(head, node);
	return (0);
}

int	remove_env(t_envp **head, const char *key)
{
	t_envp	*current;
	t_envp	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}
