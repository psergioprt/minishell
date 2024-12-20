/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:02:04 by jcavadas          #+#    #+#             */
/*   Updated: 2024/12/20 12:35:18 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO: TUDO AQUI

//function created to free the linked list
void	free_list(t_minishell *mini)
{
	t_node	*current;
	t_node	*next;

	current = mini->tokenlst;
    free(mini->command);
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
	mini->tokenlst = NULL;
}