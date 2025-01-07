/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:49:34 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/07 12:18:29 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_envvars(t_minishell *mini)
{
	int	j;

	j = 0;
	while (j < mini->env_count)
	{
		free(mini->envvars[j].key);
		free(mini->envvars[j].value);
		j++;
	}
	free(mini->envvars);
	mini->envvars = NULL;
	return ;
}

void	parse_env(t_minishell *mini, char *env[])
{
	char	*delimiter;
	int		i;
	size_t	key_len;
	size_t	value_len;

	mini->env_count = 0;
	i = 0;
	while (env[mini->env_count] != NULL)
		mini->env_count++;
	if (mini->env_count == 0)
	{
		mini->envvars = NULL;
		return ;
	}
	mini->envvars = malloc(sizeof(t_env) * (mini->env_count + 1));
	if (!mini->envvars)
	{
		perror("Failed to allocate memory for envvars");
		return ;
	}
	while (i < mini->env_count)
	{
		delimiter = ft_strchr(env[i], '=');
		if (delimiter)
		{
			key_len = delimiter - env[i];
			value_len = ft_strlen(delimiter + 1);
			mini->envvars[i].key = malloc(key_len + 1);
			mini->envvars[i].value = malloc(value_len + 1);
			if (!mini->envvars[i].key || !mini->envvars[i].value)
				free_envvars(mini);
			ft_memcpy(mini->envvars[i].key, env[i], key_len);
			mini->envvars[i].key[key_len] = '\0';
			ft_strcpy(mini->envvars[i].value, delimiter + 1);
			mini->envvars[i].print = true;
		}
		else
		{
			mini->envvars[i].key = ft_strdup(env[i]);
			if (!mini->envvars[i].key)
				free_envvars(mini);
			mini->envvars[i].value = NULL;
			mini->envvars[i].print = false;
		}
		i++;
	}
	mini->envvars[mini->env_count].key = NULL;
	mini->envvars[mini->env_count].value = NULL;
	mini->envvars[mini->env_count].print = false;
}
