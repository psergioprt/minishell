/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 07:01:28 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/30 07:22:06 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env(char *env[])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	print_nodes(t_node *command_list)
{
	int		i;
	t_node	*current;

	i = 0;
	current = command_list;
	while (current)
	{
		if (i == 0)
			printf("\033[1;33mNode[0]: %s\033[0m\n", current->token);
		else
			printf("\033[1;33mNode[%d]: %s\033[0m\n", i, current->token);
		current = current->next;
		i++;
	}
}

void	print_envvar(t_minishell *mini)
{
	t_env	*current;

	current = mini->envvars;
	while (current)
	{
		printf("Key: %s, Value: %s\n", current->key, current->value);
		current = current->next;
	}
}
