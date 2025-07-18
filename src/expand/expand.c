/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:34:12 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/18 16:54:25 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	_expand_all(t_node *node)
{
	// expand_parameter(node);
	// expand_word_splitting(node);
	expand_quote_removal(node);
}

char	*append_char(char *src, char c)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(src) + 1;
	dest = malloc(len + 1);
	if (!dest)
		return ;
	ft_strlcpy(dest, src, len);
	dest[len] = c;
	dest[len + 1] = '\0';
	free(src);
	return (dest);
}
