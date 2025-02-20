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

void	handle_value(t_minishell *mini, t_node *node, bool cat)
{
	t_env	*found_env;
	t_env	*new_env;

	new_env = export_args(node->token);
	found_env = find_key(mini, new_env->key);
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
	bool	cat;

	cat = false;
	while (node)
	{
		if (check_valid_key(node->token, &cat) == 0)
		{
			if (cat == true)
				node->token = skip_plus(node->token);
			handle_value(mini, node, cat);
		}
		else
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(node->token, 2);
			ft_putstr_fd("' is not a valid identifier\n", 2);
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
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(node->token, 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	loop_node(mini, node, &ret);
	return (ret);
}
