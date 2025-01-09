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

int	export_args(t_minishell *mini, char *var) //TODO 25 linhas, passar algo para a argumentate()?
{
	t_env		*envvars;
	t_env		*new_env;
	size_t		i;

	envvars = mini->envvars;
	i = 0;
	new_env = malloc(sizeof(t_env));
	printf("var: %s\n", var); //TODO apagar testes
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
	while (envvars->next)
	{
		envvars = envvars->next; //Ir ate ao ultimo dos envvars para adicionar o novo
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
 
//tem que adicionar mais que uma se tiver mais que uma
int	argumentate(t_minishell *mini) //TODO: testar bem isto
{
	t_node	*varlst;

	varlst = mini->tokenlst;
	varlst = varlst->next; //Passar o comando em si a frente
	while (varlst)
	{
		export_args(mini, varlst->token);
		varlst = varlst->next;
	}
	return (1);
}

int	custom_export(t_minishell *mini)
{
	t_node	*node;

	node = mini->tokenlst;
	if (!node->next)
		return (export_no_args(mini));
	else
		return (argumentate(mini));
}
