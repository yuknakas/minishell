/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:58:12 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:01:33 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_quote_state(char c, t_split_state *s)
{
	if (c == '\'' && !s->in_double)
		s->in_single = !s->in_single;
	else if (c == '"' && !s->in_single)
		s->in_double = !s->in_double;
}

static int	count_segments(const char *line)
{
	t_split_state	s;
	int				count;

	s = (t_split_state){0, 0, 0, 0};
	count = 1;
	while (line[s.i])
	{
		update_quote_state(line[s.i], &s);
		if (line[s.i] == ';' && !s.in_single && !s.in_double)
			count++;
		s.i++;
	}
	return (count);
}

static void	extract_segments(char **arr, const char *line)
{
	t_split_state	s;
	int				j;
	char			*buf;

	s = (t_split_state){0, 0, 0, 0};
	j = 0;
	while (line[s.i])
	{
		update_quote_state(line[s.i], &s);
		if (line[s.i] == ';' && !s.in_single && !s.in_double)
		{
			buf = ft_strndup(line + s.start, s.i - s.start);
			arr[j++] = buf;
			s.start = s.i + 1;
		}
		s.i++;
	}
	buf = ft_strndup(line + s.start, s.i - s.start);
	arr[j++] = buf;
	arr[j] = NULL;
}

char	**split_unquoted_semicolons(const char *line)
{
	char	**arr;
	int		count;

	if (!line)
		return (NULL);
	count = count_segments(line);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	extract_segments(arr, line);
	return (arr);
}
