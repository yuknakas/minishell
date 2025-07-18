/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:59:32 by raosmona          #+#    #+#             */
/*   Updated: 2025/07/18 16:27:47 by yuknakas         ###   ########.fr       */
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

typedef struct s_envp		t_envp;
typedef struct s_token		t_token;
typedef struct s_redir		t_redir;
typedef struct s_cmd		t_cmd;
typedef struct s_minishell	t_minishell;

typedef struct s_token
{
	char					*line;
	t_token_type			type;
	struct s_token			*next;
	int						is_expanded;
}							t_token;

typedef struct s_node
{
	t_token					*arg_list;
	t_node					*next;
}							t_node;

typedef struct s_redir
{
	t_redir_type			kind;
	char					*file;
	struct s_redir			*next;
}							t_redir;

typedef struct s_envp
{
	char					*key;
	char					*value;
	t_envp					*next;
}							t_envp;

typedef struct s_cmd
{
	char					**argv;
	t_redir					*rd;
	int						builtin;
	t_cmd					*next;
}							t_cmd;

#endif