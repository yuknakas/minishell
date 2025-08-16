/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:04:52 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:16:45 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->argv = NULL;
	cmd->rd = NULL;
	cmd->builtin = 0;
	cmd->next = NULL;
	return (cmd);
}

static int	count_args(char **argv)
{
	int	i;

	i = 0;
	if (argv != NULL)
	{
		while (argv[i] != NULL)
			i++;
	}
	return (i);
}

static void	copy_old_args(char **new_argv, char **old_argv)
{
	int	i;

	i = 0;
	if (old_argv != NULL)
	{
		while (old_argv[i] != NULL)
		{
			new_argv[i] = old_argv[i];
			i++;
		}
	}
}

int	add_arg(t_cmd *cmd, char *arg)
{
	int		argc;
	char	**new_argv;

	argc = count_args(cmd->argv);
	new_argv = (char **)malloc(sizeof(char *) * (argc + 2));
	if (new_argv == NULL)
		return (1);
	copy_old_args(new_argv, cmd->argv);
	new_argv[argc] = arg;
	new_argv[argc + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	return (0);
}
