/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:44:27 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/22 23:06:21 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_node(t_minishell *mini)
{
	int		i;
	t_node	*temp;

	i = 0;
	temp = mini->commands->tokens;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

t_env	*find_key(t_minishell *mini, char *key)
{
	t_env	*envvars;

	envvars = mini->envvars;
	while (envvars)
	{
		if (ft_strcmp(key, envvars->key) == 0)
			return (envvars);
		envvars = envvars->next;
	}
	return (NULL);
}

int	check_valid_key(char *str, bool *cat)
{
	int		i;
	bool	has_char;

	i = 0;
	has_char = false;
	if (!str || !str[i])
		return (1);
	if (str[i] == '=' || ft_isdigit(str[i]))
		return (1);
	while (str[i] != '=' && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (1);
		if (str[i] == '+' && !str[i + 1])
			return (1);
		if (str[i] == '+' && *cat == false && has_char == true)
			*cat = true;
		else if ((str[i] == '+' && *cat == true) || \
				(str[i] == '+' && has_char == false))
			return (1);
		i++;
		has_char = true;
	}
	return (0);
}

int	replace_env_value(t_env *found_env, char *value)
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
