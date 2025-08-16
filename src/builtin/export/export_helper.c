/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:10:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/16 18:12:55 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	cmp_envp_ptrs(const void *a, const void *b)
{
	const t_envp	*ea;
	const t_envp	*eb;

	ea = *(const t_envp **)a;
	eb = *(const t_envp **)b;
	return (ft_strcmp(ea->key, eb->key));
}

static void	print_env_value(const char *value)
{
	int	j;

	j = 0;
	while (value[j])
	{
		if (value[j] == '"' || value[j] == '\\')
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(value[j], STDOUT_FILENO);
		j++;
	}
}

static void	print_env_entry(t_envp *e)
{
	const char	*v;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(e->key, STDOUT_FILENO);
	if (e->value == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	ft_putstr_fd("=\"", STDOUT_FILENO);
	v = e->value;
	print_env_value(v);
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}

t_envp	**create_env_array(t_minishell *sh, int count)
{
	t_envp	**arr;
	t_envp	*cur;
	int		i;

	arr = (t_envp **)malloc(sizeof(t_envp *) * count);
	if (!arr)
		return (NULL);
	cur = sh->env;
	i = 0;
	while (cur)
	{
		arr[i++] = cur;
		cur = cur->next;
	}
	return (arr);
}

void	print_export_sorted(t_minishell *sh)
{
	int		count;
	t_envp	**arr;
	int		i;

	count = env_list_size(sh->env);
	arr = create_env_array(sh, count);
	if (!arr)
		return ;
	qsort(arr, count, sizeof(t_envp *), cmp_envp_ptrs);
	i = 0;
	while (i < count)
	{
		print_env_entry(arr[i]);
		i++;
	}
	free(arr);
}
