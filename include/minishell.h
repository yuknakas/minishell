/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razakosmonaliev <razakosmonaliev@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:51:22 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/28 20:36:23 by razakosmona      ###   ########.fr       */
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
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
# include <errno.h>
# include <sys/wait.h>

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
void							free_envp(t_envp *env);
t_envp							*copy_envp(char **envp);
void							print_envp(t_envp *env);
int								env_list_size(t_envp *env);
char							**env_list_to(t_envp *env);

// Tokenize
int								is_blank(char c);
int								is_word_start(char c);
int								take_quote(char *line, int *i);
char							*ft_strndup(const char *src, size_t n);
t_token							*new_token(char *token_line);
int								append_token(t_token **token_list,
									t_token *new_token);
t_token							*ft_last_token(t_token *token_list);
t_token							*make_token_list(char *line);

// Executing
void							readline_loop(t_minishell *sh);
int								interpret(char *line, t_minishell *sh);
int								execute(char *cmd, t_minishell *sh);
int								find_path(char *command, t_minishell *sh);
char							**_set_cmd(char *command);

// Erorrs
int								pex_putstr_int(char *str);
int								pex_puterror(char *str);
int								pex_file_error(char *file_name);
int								pex_cmd_error(char *cmd_name);
void							_freearr(char **arr);

#endif