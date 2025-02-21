/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_empty_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:52:59 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/21 20:55:09 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_token_to_list(t_minishell *mini, t_node *new_token)
{
	t_node	*current;

	if (!mini->tokenlst)
		mini->tokenlst = new_token;
	else
	{
		current = mini->tokenlst;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

void	add_empty_token(t_minishell *mini)
{
	t_node	*new_token;

	new_token = malloc(sizeof(t_node));
	check_malloc(new_token);
	new_token->token = ft_strdup("");
	check_malloc(new_token->token);
	new_token->type = NONE;
	new_token->next = NULL;
	new_token->target = NULL;
	add_token_to_list(mini, new_token);
}
