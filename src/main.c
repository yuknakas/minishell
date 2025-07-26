/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:56:56 by raosmona          #+#    #+#             */
/*   Updated: 2025/07/28 09:24:26 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/socket.h>

volatile sig_atomic_t	g_sig = 0;

void	shell_loop(t_minishell *sh)
{
	char	*line;

	(void)sh;
	while (1)
	{
		line = readline("minishell$ ");
		printf("You typed: %s\n", line);
		free(line);
	}
}

t_minishell	init_shell(char **envp)
{
	t_minishell	sh;
	t_envp		*env;

	env = copy_envp(envp);
	sh.env = env;
	return (sh);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	set_signal_handlers();
<<<<<<< HEAD
=======
	shell = init_shell(envp);
	//print_envp(shell.env);
>>>>>>> 19318f3 (little changes)
	readline_loop(envp);
	return (0);
}
