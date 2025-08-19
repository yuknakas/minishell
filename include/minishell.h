/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:51:22 by yuknakas          #+#    #+#             */
/*   Updated: 2025/08/19 14:15:04 by yuknakas         ###   ########.fr       */
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

char							*remove_quotes(const char *word);

/*--- expand_token.c ---*/
char							*expand_token_word(char *word, t_minishell *sh);

/*--- expand_simple.c ---*/
char							*expand_vars_simple(const char *word,
									t_minishell *sh);

/*--- expand_utils.c ---*/
char							*get_var_name(const char *str);
char							*lookup_var_value(const char *var_name,
									t_minishell *sh);
void							append_char_to_str(char **str, char c);

/*--- expand_handlers.c ---*/
void							handle_quotes(char c, t_exp_state *state, int *i);
void							handle_dollar(char **new_word, const char *word,
									int *i, t_minishell *sh);
void							handle_escape(char **new_word, const char *word,
									int *i, t_exp_state *state);

void							set_signal_handlers(void);
void							free_envp(t_envp *env);
t_envp							*copy_envp(char **envp);
void							print_envp(t_envp *env);
int								env_list_size(t_envp *env);
char							**env_list_to(t_envp *env);
t_cmd							*parse(t_token *tokens, t_minishell *sh);

// Tokenize
int								is_blank(char c);
int								is_word_start(char c);
int								take_quote(char *line, int *i);
char							*ft_strndup(const char *src, size_t n);
t_token							*new_token(char *token_line);
int								append_token(t_token **token_list,
									t_token *new_token);
t_token							*ft_last_token(t_token *token_list);
char							*remove_quotes(const char *word);
t_token							*make_token_list(char *line);

// builtin
int								builtin_cd(char **args, t_minishell *sh);
int								cd_get_home_path(t_minishell *sh,
									const char **out_path);
int								cd_get_oldpwd(t_minishell *sh,
									const char **out_path);
int								resolve_cd_path(char **args, t_minishell *sh,
									const char **out_path, char **out_old_pwd);
int								builtin_echo(char **args);
int								builtin_pwd(void);
int								builtin_env(t_minishell *sh);
int								builtin_exit(char **args, t_minishell *sh);
int								builtin_export(char **args, t_minishell *sh);
int								builtin_unset(char **args, t_minishell *sh);

// Executing
void							shell_loop(t_minishell *sh);
int								interpret(char *line, t_minishell *sh);
int								execute(char *cmd, t_minishell *sh);
int								find_path(char *command, t_minishell *sh);
char							*get_cmd_path(char *command, t_minishell *sh);
char							**_set_cmd(char *command);
int								execute_pipeline(t_cmd *cmds, t_minishell *sh);
int								execute_single_command(t_cmd *cmd,
									t_minishell *sh);
int								ft_strcmp(const char *s1, const char *s2);

/*--- execute_pipeline.c ---*/
int								execute_pipeline(t_cmd *cmds, t_minishell *sh);

/*--- execute_command.c ---*/
int								execute_single_command(t_cmd *cmd,
									t_minishell *sh);
int								execute_builtin(t_cmd *cmd, t_minishell *sh);
int								execute_external_command(t_cmd *cmd,
									t_minishell *sh);

/*--- execute_redirects.c ---*/
int								handle_redirections(t_cmd *cmd,
									t_minishell *sh);
int								open_redir_file(t_redir *redir,
									t_minishell *sh);

/*--- execute_heredoc.c ---*/
int								handle_heredoc(t_cmd *cmd, t_redir *redir, t_minishell *sh);
// int								handle_heredoc(t_redir *redir, t_minishell *sh);

/*--- tokenizer.c ---*/
t_token							*make_token_list(char *line);

/*--- token_creation.c ---*/
int								word_token(char **line, t_token **token_list);
int								operator_token(char **line,
									t_token **token_list);

/*--- token_list_utils.c ---*/
t_token							*new_token(char *token_line);
int								append_token(t_token **token_list,
									t_token *new_token);
t_token							*ft_last_token(t_token *token_list);

/*--- token_op_utils.c ---*/
int								is_operator(char *s);
int								detect_operator(const char *s, t_operator *op,
									int *len);

/*--- token_word_utils.c ---*/
int								is_blank(char c);
int								take_quote(char *line, int *i);

/*--- tokenizer.c ---*/
t_token							*make_token_list(char *line);

/*--- token_creation.c ---*/
int								word_token(char **line, t_token **token_list);
int								operator_token(char **line,
									t_token **token_list);

/*--- token_list_utils.c ---*/
t_token							*new_token(char *token_line);
int								append_token(t_token **token_list,
									t_token *new_token);
t_token							*ft_last_token(t_token *token_list);

/*--- token_op_utils.c ---*/
int								is_operator(char *s);
int								detect_operator(const char *s, t_operator *op,
									int *len);

/*--- token_word_utils.c ---*/
int								is_blank(char c);
int								take_quote(char *line, int *i);

/*--- parser.c ---*/
t_cmd							*parse(t_token *tokens, t_minishell *sh);

/*--- parser_cmd_utils.c ---*/
t_cmd							*init_cmd(void);
int								add_arg(t_cmd *cmd, char *arg);

/*--- parser_redir_utils.c ---*/
int								add_redir(t_cmd *cmd, t_token *token,
									t_minishell *sh);

// Expand
char							*expand_token_word(char *word, t_minishell *sh);
char							*expand_vars_simple(const char *word,
									t_minishell *sh);

/*--- main_loop.c ---*/
void							shell_loop(t_minishell *sh);

/*--- split_line.c ---*/
char							**split_unquoted_semicolons(const char *line);

/*--- errors.c ---*/
int								pex_perror(char *cmd);
int								pex_file_error(char *file_name);
int								pex_cmd_error(char *cmd_name);

/*--- memory_utils.c ---*/
void							free_token_list(t_token *tokens);
void							free_redir_list(t_redir *redir);
void							free_cmd_list(t_cmd *cmds);
void							_freearr(char **arr);

/*--- string_utils.c ---*/
char							*remove_quotes(const char *word);

// Erorrs
int								pex_putstr_int(char *str);
int								pex_perror(char *cmd);
/* system errors (uses perror) */
int								pex_print(char *cmd, char *msg);
/* plain minishell: cmd: msg */
int								pex_print_arg(char *cmd, char *arg, char *msg);
/* minishell: cmd: arg: msg */
int								pex_file_error(char *file_name);
int								pex_cmd_error(char *cmd_name);
void							_freearr(char **arr);

// Free
void							free_token_list(t_token *tokens);
void							free_cmd_list(t_cmd *cmds);
void							free_env_array_on_fail(char **arr, int count);

// Env
t_envp							*find_env_node(t_envp *head, const char *key);
int								is_valid_env_key(const char *key);
int								add_or_update_env(t_envp **head,
									const char *key, const char *value);
int								remove_env(t_envp **head, const char *key);

#endif