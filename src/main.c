/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:56:56 by raosmona          #+#    #+#             */
/*   Updated: 2025/07/26 21:19:22 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO: init_shell(), shell_loop()

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

void	init_shell(char **envp)
{
	t_minishell	sh;
	
	sh.env = copy_envp(envp);
	print_envp(sh.env);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	set_signal_handlers();
	readline_loop(envp);
	return (0);
}
