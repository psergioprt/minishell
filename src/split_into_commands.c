/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:57 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/29 15:13:57 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_cmd *create_new_cmd()
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->tokens = NULL;
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->next = NULL;
	return (cmd);
}

static void add_token_to_cmd(t_cmd *cmd, t_node *current)
{
	t_node **token_tail;

	token_tail = &cmd->tokens;
	while (*token_tail)
		token_tail = &((*token_tail)->next);
	*token_tail = malloc(sizeof(t_node));
	if (!*token_tail)
		return;
	(*token_tail)->token = ft_strdup(current->token);
	(*token_tail)->type = current->type;
	(*token_tail)->next = NULL;
}

void split_commands(t_minishell *mini)
{
	t_node *current;
	t_cmd *last_cmd;
	t_cmd *new_cmd;
	
	current = mini->tokenlst;
	last_cmd = NULL;
	mini->commands = NULL;
	while (current)
	{
		new_cmd = create_new_cmd();
		if (!new_cmd)
			return;
		while (current && ft_strcmp(current->token, "|") != 0)
		{
			add_token_to_cmd(new_cmd, current);
			current = current->next;
		}
		if (last_cmd)
			last_cmd->next = new_cmd;
		else
			mini->commands = new_cmd;
		last_cmd = new_cmd;
		if (current)
			current = current->next;
	}
}
