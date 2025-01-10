/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_envvar_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:57:59 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/09 22:19:20 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	add_env_var(t_env **envvars, const char *key, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("malloc");
		exit(1);
	}
	new_var->key = strdup(key);
	new_var->value = strdup(value);
	new_var->print = true;
	new_var->next = *envvars;
	*envvars = new_var;
}*/

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
/*
void	create_custom_envvars(t_minishell *mini)
{
	add_env_var(&(mini->envvars), "MY_VAR", "hello");
	add_env_var(&(mini->envvars), "USER_NAME", "minishell_user");
}*/

void	free_envvars(t_minishell *mini)
{
	t_env	*current;
	t_env	*next;

	current = mini->envvars;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}
