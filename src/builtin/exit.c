/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:40:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/19 17:01:10 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_minishell *sh)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			pex_print_arg("exit", args[1], "numeric argument required");
			exit(2);
		}
		if (args[2])
		{
			pex_print("exit", "too many arguments");
			return (1);
		}
		exit_code = ft_atoi(args[1]);
	}
	else
		exit_code = sh->last_status;
	free_envp(sh->env);
	exit(exit_code);
}
