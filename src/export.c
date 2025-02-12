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
		if (envvars->print)
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
	return (new_env);
}

void	argumentate(t_minishell *mini, t_env *new_env)
{
	t_env	*envvars;

	envvars = mini->envvars;
	while (envvars->next)
	{
		envvars = envvars->next;
	}
	envvars->next = new_env;
	new_env->next = NULL;
}

void	cat_env_value(t_env *found_env, t_env *new_env, t_node *node)
{
	char	*new_value;

	if (!found_env->value || found_env->value[0] == '\0')
		replace_env_value(found_env, node->token);
	else
	{
		new_value = ft_strjoin(found_env->value, new_env->value);
		free(found_env->value);
		found_env->value = new_value;
	}
}

void	handle_value(t_minishell *mini, t_node *node, t_env *found_env, \
		t_env *new_env, bool cat)
{
	if (cat == false)
	{
		if (found_env != NULL)
			replace_env_value(found_env, node->token);
		else
			argumentate(mini, new_env);
	}
	else
	{
		if (found_env != NULL)
			cat_env_value(found_env, new_env, node);
		else
			argumentate(mini, new_env);
	}
}

void	loop_node(t_minishell *mini, t_node *node, int *ret)
{
	t_env	*found_env;
	t_env	*new_env;
	bool	cat;

	cat = false;
	while (node)
	{
		if (check_valid_key(node->token, &cat) == 0)
		{
			if (cat == true)
				node->token = skip_plus(node->token);
			new_env = export_args(node->token);
			found_env = find_key(mini, new_env->key);
			handle_value(mini, node, found_env, new_env, cat);
		}
		else
		{
			printf("export: '%s' is not a valid identifier\n", node->token);
			*ret = 1;
		}
		cat = false;
		node = node->next;
	}
}

int	custom_export(t_minishell *mini)
{
	t_node	*node;
	int		ret;

	ret = 0;
	node = mini->commands->tokens;
	if (!node->next)
		return (export_no_args(mini));
	node = node->next;
	if (node->token[0] == '-' && node->token[1])
	{
		printf("export: %s: invalid option\n", node->token);
		return (2);
	}
	loop_node(mini, node, &ret);
	return (ret);
}
