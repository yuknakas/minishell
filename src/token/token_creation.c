/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:04:30 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:04:31 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token_type	get_op_type(t_operator op)
{
	if (op == OP_DGREAT)
		return (TOKEN_DGREAT);
	if (op == OP_DLESS)
		return (TOKEN_DLESS);
	if (op == OP_AND)
		return (TOKEN_AND);
	if (op == OP_OR)
		return (TOKEN_OR);
	if (op == OP_GREAT)
		return (TOKEN_REDIR_OUT);
	if (op == OP_LESS)
		return (TOKEN_REDIR_IN);
	if (op == OP_PIPE)
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

int	operator_token(char **line, t_token **token_list)
{
	t_operator	op;
	int			len;
	char		*token_str;
	t_token		*new;

	if (!detect_operator(*line, &op, &len))
		return (1);
	token_str = ft_strndup(*line, len);
	if (!token_str)
		return (1);
	new = new_token(token_str);
	if (!new)
		return (free(token_str), 1);
	new->type = get_op_type(op);
	if (append_token(token_list, new))
	{
		free(new->line);
		free(new);
		return (1);
	}
	*line += len;
	return (0);
}

int	word_token(char **line, t_token **token_list)
{
	char	*token_line;
	int		i;

	i = 0;
	while ((*line)[i] && !is_blank((*line)[i]) && !is_operator(&(*line)[i]))
	{
		if ((*line)[i] == '\'' || (*line)[i] == '"')
		{
			if (take_quote(&(*line)[i], &i))
				return (1);
			else
				continue ;
		}
		i++;
	}
	token_line = ft_strndup(*line, i);
	if (append_token(token_list, new_token(token_line)))
		return (1);
	*line += i;
	return (0);
}
