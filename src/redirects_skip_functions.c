/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_skip_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:19:26 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/21 00:22:45 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_redirection_plus_target_cmd_support(t_node **current, \
	t_node **tmp, t_node **prev, t_node **tokens)
{
	t_node	*target_node;

	*tmp = *current;
	*current = (*current)->next;
	if (*current)
	{
		target_node = *current;
		*current = (*current)->next;
		free(target_node->token);
		free(target_node);
	}
	free((*tmp)->token);
	free(*tmp);
	if (*prev)
		(*prev)->next = *current;
	else
		*tokens = *current;
}

void	skip_redirection_plus_target_cmd(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	t_node	*prev;
	t_node	*current;
	t_node	*tmp;

	cmd = cmd_list;
	while (cmd)
	{
		prev = NULL;
		current = cmd->tokens;
		while (current)
		{
			if (current->type == PIPE)
				break ;
			if (current->type != NONE && current->type != HEREDOC)
				skip_redirection_plus_target_cmd_support(&current, &tmp, \
					&prev, &cmd->tokens);
			else
			{
				prev = current;
				current = current->next;
			}
		}
		cmd = cmd->next;
	}
}

void	skip_redirection_plus_target_support(t_node **current, t_node **tmp)
{
	t_node	*target_node;

	*tmp = *current;
	*current = (*current)->next;
	if (*current)
	{
		target_node = *current;
		*current = (*current)->next;
		free(target_node->token);
		free(target_node);
	}
	free((*tmp)->token);
	free(*tmp);
}

void	skip_redir(t_minishell *mini, t_node **current, t_node **prev)
{
	t_node	*tmp;

	skip_redirection_plus_target_support(current, &tmp);
	if (*prev)
		(*prev)->next = *current;
	else
		mini->tokenlst = *current;
}

void	skip_redirection_plus_target(t_minishell *mini)
{
	t_node	*prev;
	t_node	*current;

	prev = NULL;
	current = mini->tokenlst;
	skip_redirection_plus_target_cmd(mini->commands);
	while (current && current->type != PIPE)
	{
		if (current->type != NONE && current->type != HEREDOC)
			skip_redir(mini, &current, &prev);
		else
		{
			prev = current;
			current = current->next;
		}
	}
	current = mini->tokenlst;
	remove_heredoc_token(mini);
}
