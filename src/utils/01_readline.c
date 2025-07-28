/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:26:41 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/28 20:28:31 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		interpret(char *line, t_minishell *sh);

void	readline_loop(t_minishell *sh)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, sh);
		free(line);
	}
	exit(0);
}

int	interpret(char *line, t_minishell *sh)
{
	int		ret_val;
	pid_t	id;

	id = fork();
	if (id < 0)
	{
		printf("error fork");
		return (-1);
	}
	if (id == 0)
	{
		ret_val = execute(line, sh);
		exit(ret_val);
	}
	if (id != 0)
	{
		waitpid(id, &ret_val, 0);
		return (WEXITSTATUS(ret_val));
	}
	return (0);
}
