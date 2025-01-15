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
int	argumentate(t_minishell *mini, t_node *node)
{
	export_args(mini, node->token);
	return (1);
}

int	replace_value(t_env *found_env, char *value)
{
	int	i;

	i = 0;
	while (value[i] != '=' && value[i] != '\0')
		i++;
	if (value[i] == '=' && value[i + 1] != '\0')
	{
		free(found_env->value);
		found_env->value = ft_strdup(value + i + 1);
		found_env->print = true;
	}
	else if (value[i] == '=')
	{
		free(found_env->value);
		found_env->value = ft_strdup("");
		found_env->print = true;
	}
	return (1);
}

int	custom_export(t_minishell *mini)
{
	t_node	*node;
	t_env	*found_env;

	node = mini->tokenlst;
	if (!node->next)
		return (export_no_args(mini));

	node = node->next; //Passar o comando em si a frente
	while (node)
	{
		found_env = find_key(mini, node->token);
		//TODO se tiver espacos com \ antes tem de considerar espaco no value - Parsing?
		if (check_valid_key(node->token) == 0) //analisar chars especiais - Key nao pode ter
		{
			if (found_env != NULL) //key ja existe, fazer troca de valor
			{
				printf("found_env->key: %s\n", found_env->key);//TODO apagar
				replace_value(found_env, node->token);
				//TODO apagar
				//se ja existir a key, e o novo tiver um = so, troca o value para ""
				//Se ja existir a key e o novo tiver um = e value, troca o value para o novo
				//Se ja existir mas a key nao tiver =, nao muda nada
			}
			else
				argumentate(mini, node);
		}
		else
			printf("export: %s is not a valid identifier\n", node->token);
		node = node->next;
	}
	return (1);
}
