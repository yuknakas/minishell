/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:56:56 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/14 14:42:24 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/socket.h>

volatile sig_atomic_t	g_sig = 0;

t_minishell	init_shell(char **envp)
{
	t_minishell	sh;
	t_envp		*env;

	env = copy_envp(envp);
	sh.env = env;
	sh.last_status = 0;
	sh.tokens = NULL;
	sh.cmds = NULL;
	return (sh);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	if (argc != 1)
	{
		printf("minishell: %s: %s\n", argv[0], "Must be run without arguments");
		return (1);
	}
	set_signal_handlers();
	shell = init_shell(envp);
	shell_loop(&shell);
	free_envp(shell.env);
	return (0);
}
