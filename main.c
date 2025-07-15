/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:56:56 by raosmona          #+#    #+#             */
/*   Updated: 2025/07/08 16:54:12 by raosmona         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	(void)argc;
	(void)argv;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
