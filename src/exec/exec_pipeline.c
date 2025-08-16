/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:06:18 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:06:26 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	first_child_process(t_cmd *cmds, t_minishell *sh, int *p_fd)
{
	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	exit(execute_single_command(cmds, sh));
}

static void	second_child_process(t_cmd *cmds, t_minishell *sh, int *p_fd)
{
	close(p_fd[1]);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	exit(execute_pipeline(cmds->next, sh));
}

static int	wait_for_children(pid_t pid1, pid_t pid2, t_minishell *sh)
{
	int	status;

	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		sh->last_status = WEXITSTATUS(status);
	return (sh->last_status);
}

int	execute_pipeline(t_cmd *cmds, t_minishell *sh)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (cmds == NULL)
		return (0);
	if (cmds->next == NULL)
		return (execute_single_command(cmds, sh));
	if (pipe(pipe_fd) == -1)
		return (pex_perror("pipe"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (pex_perror("fork"), 1);
	if (pid1 == 0)
		first_child_process(cmds, sh, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
		return (pex_perror("fork"), 1);
	if (pid2 == 0)
		second_child_process(cmds, sh, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (wait_for_children(pid1, pid2, sh));
}
