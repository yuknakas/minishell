/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:13:59 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/21 15:30:56 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_redir_kind(t_redir *redir, t_token *token)
{
	if (token->type == TOKEN_REDIR_IN)
		redir->kind = REDIR_IN;
	else if (token->type == TOKEN_REDIR_OUT)
		redir->kind = REDIR_OUT;
	else if (token->type == TOKEN_DLESS)
		redir->kind = REDIR_HEREDOC;
	else if (token->type == TOKEN_DGREAT)
		redir->kind = REDIR_APPEND;
}

static void	setup_redir_file(t_redir *redir, t_token *token, t_minishell *sh)
{
	int	has_quote;

	if (redir->kind == REDIR_HEREDOC)
	{
		has_quote = (ft_strchr(token->next->line, '\'') != NULL)
			|| (ft_strchr(token->next->line, '"') != NULL);
		redir->file = remove_quotes(token->next->line);
		redir->no_expand = has_quote;
	}
	else
	{
		redir->file = expand_token_word(token->next->line, sh);
		redir->no_expand = 0;
	}
}

static void	append_redir_to_cmd(t_cmd *cmd, t_redir *redir)
{
	t_redir	*last;

	redir->next = NULL;
	if (cmd->rd == NULL)
		cmd->rd = redir;
	else
	{
		last = cmd->rd;
		while (last->next != NULL)
			last = last->next;
		last->next = redir;
	}
}

int	add_redir(t_cmd *cmd, t_token *token, t_minishell *sh)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (redir == NULL)
		return (1);
	set_redir_kind(redir, token);
	setup_redir_file(redir, token, sh);
	append_redir_to_cmd(cmd, redir);
	return (0);
}
