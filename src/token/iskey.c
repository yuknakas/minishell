/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iskey.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:40:36 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/15 16:00:03 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_word_start(char c)
{
	return (c && !is_blank(c));
}

void	take_blank(char **str)
{
	while (is_blank(**str))
		*str++;
	return ;
}

void	take_sin_quote(char **str)