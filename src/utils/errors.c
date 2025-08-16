/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:03:51 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:10:24 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

int	pex_perror(char *cmd)
{
	if (!cmd)
		perror("minishell");
	else
	{
		fprintf(stderr, "minishell: %s: ", cmd);
		perror("");
	}
	return (-1);
}

int	pex_file_error(char *file_name)
{
	if (!file_name)
	{
		fprintf(stderr, "minishell: ");
		perror("");
		return (-1);
	}
	fprintf(stderr, "minishell: %s: ", file_name);
	perror("");
	return (-1);
}

int	pex_cmd_error(char *cmd_name)
{
	if (!cmd_name)
		return (-1);
	fprintf(stderr, "minishell: %s: command not found\n", cmd_name);
	return (-1);
}
