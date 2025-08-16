/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:59:32 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/16 18:02:29 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_EOF,
}							t_token_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}							t_redir_type;

typedef enum e_operator
{
	OP_NONE,
	OP_DGREAT,
	OP_DLESS,
	OP_AND,
	OP_OR,
	OP_GREAT,
	OP_LESS,
	OP_PIPE,
	OP_SEMI
}							t_operator;

typedef struct s_envp		t_envp;
typedef struct s_token		t_token;
typedef struct s_redir		t_redir;
typedef struct s_cmd		t_cmd;
typedef struct s_minishell	t_minishell;

typedef struct s_redir
{
	t_redir_type			kind;
	char					*file;
	int						no_expand;
	struct s_redir			*next;
}							t_redir;

typedef struct s_envp
{
	char					*key;
	char					*value;
	t_envp					*next;
}							t_envp;

typedef struct s_token
{
	char					*line;
	t_token_type			type;
	struct s_token			*next;
	int						is_expanded;
}							t_token;

typedef struct s_cmd
{
	char					**argv;
	t_redir					*rd;
	int						builtin;
	t_cmd					*next;
}							t_cmd;

typedef struct s_split_state
{
	int						i;
	int						start;
	int						in_single;
	int						in_double;
}							t_split_state;

typedef struct s_exp_state
{
	int						in_squote;
	int						in_dquote;
}							t_exp_state;

#endif