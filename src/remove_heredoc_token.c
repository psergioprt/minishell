/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_heredoc_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 23:05:44 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/10 23:05:44 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_heredoc_token(t_minishell *mini, t_node **current_token, \
	t_node **prev_token)
{
	t_node	*heredoc_token;
	t_node	*delim_token;

	while (*current_token && (*current_token)->type == HEREDOC)
	{
		heredoc_token = *current_token;
		*current_token = (*current_token)->next;
		if (!*current_token)
			break ;
		delim_token = *current_token;
		*current_token = (*current_token)->next;
		free(delim_token->token);
		free(delim_token);
		free(heredoc_token->token);
		free(heredoc_token);
	}
	if (*prev_token)
		(*prev_token)->next = *current_token;
	else
		mini->tokenlst = *current_token;
}

void	support_heredoc_token_tokens(t_minishell *mini)
{
	t_node	*prev_token;
	t_node	*current_token;

	prev_token = NULL;
	current_token = mini->tokenlst;
	while (current_token)
	{
		if (current_token->type == PIPE)
			break ;
		if (current_token->type == HEREDOC)
			process_heredoc_token(mini, &current_token, &prev_token);
		else
		{
			prev_token = current_token;
			current_token = current_token->next;
		}
	}
}

void	process_heredoc_command(t_minishell *mini, t_node **current_cmd, \
	t_node **prev_cmd)
{
	t_node	*heredoc_cmd;
	t_node	*delim_cmd;

	while (*current_cmd && (*current_cmd)->type == HEREDOC)
	{
		heredoc_cmd = *current_cmd;
		*current_cmd = (*current_cmd)->next;
		if (!*current_cmd)
			break ;
		delim_cmd = *current_cmd;
		*current_cmd = (*current_cmd)->next;
		free(delim_cmd->token);
		free(delim_cmd);
		free(heredoc_cmd->token);
		free(heredoc_cmd);
	}
	if (*prev_cmd)
		(*prev_cmd)->next = *current_cmd;
	else
		mini->commands->tokens = *current_cmd;
}

void	support_heredoc_token_commands(t_minishell *mini)
{
	t_node	*prev_cmd;
	t_node	*current_cmd;

	prev_cmd = NULL;
	current_cmd = mini->commands->tokens;
	while (current_cmd)
	{
		if (current_cmd->type == PIPE)
			break ;
		if (current_cmd->type == HEREDOC)
			process_heredoc_command(mini, &current_cmd, &prev_cmd);
		else
		{
			prev_cmd = current_cmd;
			current_cmd = current_cmd->next;
		}
	}
}

void	remove_heredoc_token(t_minishell *mini)
{
	support_heredoc_token_tokens(mini);
	support_heredoc_token_commands(mini);
}
