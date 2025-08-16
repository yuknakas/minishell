/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:44:38 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/04 17:01:19 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_cd(char **args, t_minishell *sh)
{
	const char	*path;

	(void)sh;
	if (args[1])
		path = args[1];
	else
		path = getenv("HOME");
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
