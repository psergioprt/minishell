/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:10:55 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/08 23:10:55 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export_no_args(t_minishell *mini)
{
	t_env	*envvars;

	envvars = mini->envvars;
	while (envvars)
	{
		printf("declare -x %s", envvars->key);
		if(envvars->print)
		{
			printf("=");
			printf("\"%s\"", envvars->value);
		}
		printf("\n");
		envvars = envvars->next;
	}
	return (1);
}


int	export_args(t_minishell *mini)
{
	t_env		*envvars;
	t_env		*new_env;
	char		*var;
	size_t		i;

	envvars = mini->envvars;
	var = mini->tokenlst->next->token;
	i = 0;
	new_env = malloc(sizeof(t_env));
	printf("var: %s\n", var); //TODO apagar testes
	while (envvars->next)
	{
		envvars = envvars->next; //Ir ate ao ultimo dos envvars para adicionar o novo
	}
	while (var[i] != '=' && var[i] != '\0')
		i++;
	new_env->key = malloc(i + 1);
	ft_strlcpy(new_env->key, var, i + 1);
	if (var[i] == '=')
	{
		new_env->print = true;
		new_env->value = ft_strdup(var + i + 1);
	}
	else
	{
		new_env->print = false;
		new_env->value = ft_strdup("");
	}
	envvars->next = new_env;
	new_env->next = NULL;

	printf("KEY: %s", new_env->key); //TODO apagar testes
	printf("Value: %s", new_env->value); //TODO apagar testes
	if (new_env->print)
		printf("Has print\n");
	else
		printf("Doesn't have print\n");

	return (1);
}
 
int	custom_export(t_minishell *mini)
{
	t_node	*node;

	node = mini->tokenlst;
	if (!node->next)
		return (export_no_args(mini));
	else
		return (export_args(mini));
}
