/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:02:04 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/10 16:01:43 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO: TUDO AQUI
//TODO free envvars
void	free_envvars(t_minishell *mini)
{
	t_env	*envvars;
	t_env	*envvars_next;

	free(mini->envp); //TODO
	envvars = mini->envvars;
	while (envvars)
	{
		envvars_next = envvars->next;
		free(envvars->key);
		free(envvars->value);
		free(envvars);
		envvars = envvars_next;
	}
	mini->envvars = NULL;
}

//function created to free the linked list
void	free_list(t_minishell *mini)
{
	t_node	*current;
	t_node	*next;

	current = mini->tokenlst;
    //free(mini->command);
	//free_envvars(mini);
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
	mini->tokenlst = NULL;
}
