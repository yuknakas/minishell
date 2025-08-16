/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors-2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:09:58 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:10:27 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pex_print(char *cmd, char *msg)
{
	if (!cmd || !msg)
		return (-1);
	fprintf(stderr, "minishell: %s: %s\n", cmd, msg);
	return (-1);
}

int	pex_print_arg(char *cmd, char *arg, char *msg)
{
	if (!cmd || !arg || !msg)
		return (-1);
	fprintf(stderr, "minishell: %s: %s: %s\n", cmd, arg, msg);
	return (-1);
}

int	pex_putstr_int(char *str)
{
	if (!str)
		return (-1);
	ft_putstr_fd(str, STDERR_FILENO);
	return (-1);
}
