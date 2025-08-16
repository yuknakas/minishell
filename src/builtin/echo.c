/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:40:00 by razakosmona       #+#    #+#             */
/*   Updated: 2025/08/16 15:07:28 by razakosmona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_escaped(const char *s)
{
	while (*s)
	{
		if (*s == '\\' && *(s + 1))
		{
			s++;
			if (*s == 'n')
				write(STDOUT_FILENO, "\n", 1);
			else if (*s == 't')
				write(STDOUT_FILENO, "\t", 1);
			else if (*s == '\\')
				write(STDOUT_FILENO, "\\", 1);
			else
				write(STDOUT_FILENO, s, 1);
			s++;
		}
		else
		{
			write(STDOUT_FILENO, s, 1);
			s++;
		}
	}
}

static int	parse_flag_chars(const char *s, int *p_flag_n, int *p_flag_e)
{
	int	k;

	k = 1;
	if (s[k] == '\0')
		return (0);
	while (s[k])
	{
		if (s[k] == 'n')
			*p_flag_n = 1;
		else if (s[k] == 'e')
			*p_flag_e = 1;
		else
			return (0);
		k++;
	}
	return (1);
}

static int	parse_echo_flags(char **args, int *p_i, int *p_flag_n,
		int *p_flag_e)
{
	int	i;

	i = *p_i;
	*p_flag_n = 0;
	*p_flag_e = 0;
	while (args[i] && args[i][0] == '-')
	{
		if (!parse_flag_chars(args[i], p_flag_n, p_flag_e))
			break ;
		i++;
	}
	*p_i = i;
	return (0);
}

static void	run_echo_print(char **args, int i, int flag_e)
{
	while (args[i])
	{
		if (flag_e)
			print_escaped(args[i]);
		else
			ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

int	builtin_echo(char **args)
{
	int	i;
	int	flag_n;
	int	flag_e;

	i = 1;
	parse_echo_flags(args, &i, &flag_n, &flag_e);
	run_echo_print(args, i, flag_e);
	if (!flag_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
