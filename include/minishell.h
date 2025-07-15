/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:51:22 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/15 14:01:25 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// structs
# include "structs.h"

// Libft
# include "../libft/header/libft.h"

// Standard C libraries
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

// File & Directory
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

// Process control
# include <signal.h>
# include <sys/wait.h>

// Terminal & Readline
# include <readline/history.h>
# include <readline/readline.h>
# include <term.h>
# include <termios.h>

// Pipe
# include <sys/wait.h>
# include <errno.h>

extern volatile sig_atomic_t	g_sig;

typedef enum e_status
{
	STATUS_OK = 0,
	STATUS_SYNTAX_ERROR = 258,
	STATUS_CMD_NOT_FOUND = 127,
}								t_status_code;

typedef struct s_minishell
{
	t_envp						*env;
	int							last_status;
	t_token						*tokens;
	t_cmd						*cmds;
}								t_minishell;

void							set_signal_handlers(void);

// Executing
int			execute(char *cmd);
int			find_path(char *command);
char		**_set_cmd(char *command);

// Erorrs
int		pex_putstr_int(char *str);
int		pex_puterror(char *str);
int		pex_file_error(char *file_name);
int		pex_cmd_error(char *cmd_name);
void	_freearr(char **arr);

#endif