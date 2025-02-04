/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:45:31 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/04 17:36:37 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_string(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

t_node	*flag_checker(t_node *node, bool *has_flag)
{
	int	i;

	while (node)
	{
		i = 0;
		if (node->token[i] == '-')
		{
			i++;
			if (node->token[i] == '\0')
				return (node);
			while (node->token[i] == 'n')
				i++;
			if (node->token[i] == '\0')
				*has_flag = true;
			else
				return (node);
		}
		else
			return (node);
		node = node->next;
	}
	return (node);
}

int	custom_echo(t_minishell *mini)
{
	int		first;
	t_node	*node;
	bool	has_flag;

	first = 1;
	has_flag = false;
	node = mini->commands->tokens;
	node = node->next;
	node = flag_checker(node, &has_flag);
	while (node)
	{
		if (!first)
			write(1, " ", 1);
		write_string(node->token);
		first = 0;
		node = node->next;
	}
	if (!has_flag)
		write(1, "\n", 1);
	return (0);
}
