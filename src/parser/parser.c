/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuknakas <yuknakas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:17:02 by raosmona          #+#    #+#             */
/*   Updated: 2025/08/19 13:09:20 by yuknakas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	process_word_token(t_cmd *cmd, t_token *token, t_minishell *sh)
{
	char	*expanded_arg;

	expanded_arg = expand_token_word(token->line, sh);
	add_arg(cmd, expanded_arg);
}

static void	process_redir_token(t_cmd *cmd, t_token **token, t_minishell *sh)
{
	add_redir(cmd, *token, sh);
	*token = (*token)->next;
}

static void	process_tokens(t_token *tokens, t_cmd *head, t_minishell *sh)
{
	t_cmd	*current_cmd;
	t_token	*current_token;
	int		id;

	current_cmd = head;
	current_token = tokens;
	id = 2;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_WORD)
			process_word_token(current_cmd, current_token, sh);
		else if (current_token->type >= TOKEN_REDIR_IN
			&& current_token->type <= TOKEN_DGREAT)
			process_redir_token(current_cmd, &current_token, sh);
		else if (current_token->type == TOKEN_PIPE)
		{
			current_cmd->next = init_cmd();
			current_cmd = current_cmd->next;
			current_cmd->cmd_no = id++;
		}
		if (current_token)
			current_token = current_token->next;
	}
}

/*
** Parses a list of tokens into a linked list of command structures (t_cmd).
*/
t_cmd	*parse(t_token *tokens, t_minishell *sh)
{
	t_cmd	*head;

	head = init_cmd();
	head->cmd_no = 1;
	if (head == NULL)
		return (NULL);
	process_tokens(tokens, head, sh);
	return (head);
}
