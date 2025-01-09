/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:33:38 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/09 15:33:38 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_node(t_minishell *mini)
{
	int		i;
	t_node	*temp;

	i = 0;
	temp = mini->tokenlst; // Temporary pointer for counting
	while (temp) {
		i++;
		temp = temp->next;
	}
	return (i);
}
