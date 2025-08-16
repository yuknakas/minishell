/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_op_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:04:18 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:04:19 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator(char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '|' || *s == '>' || *s == '<' || *s == '&' || *s == ';')
		return (1);
	return (0);
}

static int	detect_double_op(const char *s, t_operator *op, int *len)
{
	if (s[0] == '>' && s[1] == '>')
	{
		*op = OP_DGREAT;
		*len = 2;
		return (1);
	}
	if (s[0] == '<' && s[1] == '<')
	{
		*op = OP_DLESS;
		*len = 2;
		return (1);
	}
	if (s[0] == '&' && s[1] == '&')
	{
		*op = OP_AND;
		*len = 2;
		return (1);
	}
	if (s[0] == '|' && s[1] == '|')
	{
		*op = OP_OR;
		*len = 2;
		return (1);
	}
	return (0);
}

int	detect_operator(const char *s, t_operator *op, int *len)
{
	*op = OP_NONE;
	*len = 0;
	if (!s[0])
		return (0);
	if (detect_double_op(s, op, len))
		return (1);
	if (s[0] == '>')
		return (*op = OP_GREAT, *len = 1, 1);
	if (s[0] == '<')
		return (*op = OP_LESS, *len = 1, 1);
	if (s[0] == '|')
		return (*op = OP_PIPE, *len = 1, 1);
	if (s[0] == ';')
		return (*op = OP_SEMI, *len = 1, 1);
	return (0);
}
