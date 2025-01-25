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
	return (0);
}

t_env	*export_args(char *var)
{
	t_env		*new_env;
	size_t		i;

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

	//TODO apagar testes
 	printf("KEY: %s\n", new_env->key); 
	printf("Value: %s\n", new_env->value); 
	if (new_env->print)
		printf("Has print\n");
	else
		printf("Doesn't have print\n");
	//TODO apagar testes

	return (new_env);
}
 
//tem que adicionar mais que uma se tiver mais que uma
void	argumentate(t_minishell *mini, t_node *node)
{
	t_env	*envvars;
	t_env	*new_env;

	envvars = mini->envvars;
	new_env = export_args(node->token);
	while (envvars->next)
	{
		envvars = envvars->next;
	}
	envvars->next = new_env;
	new_env->next = NULL;
}

void loop_node(t_minishell *mini, t_node *node, int *ret)
{
	t_env	*found_env;

	while (node)
	{
		found_env = find_key(mini, node->token);
		if (check_valid_key(node->token) == 0) //analisar chars especiais - Key nao pode ter
		{
			if (found_env != NULL) //key ja existe, fazer troca de valor
				replace_env_value(found_env, node->token);
			else
				argumentate(mini, node);
		}
		else
		{
			printf("export: %s is not a valid identifier\n", node->token);
			*ret = 1;
		}
		node = node->next;
	}
}

int	custom_export(t_minishell *mini)
{
	t_node	*node;
	int		ret;

	ret = 0;
	node = mini->tokenlst;
	if (!node->next)
		return (export_no_args(mini));
	node = node->next; //Passar o comando em si a frente
	if (node->token[0] == '-' && node->token[1])
	{
		printf("export: %s: invalid option\n", node->token);
		return (2);
	}
	loop_node(mini, node, &ret);
	return (ret);
}
