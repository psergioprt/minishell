/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:49:37 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/11 23:17:38 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(char *env_name, t_minishell *mini)
{
	t_env	*current;

	if (!env_name || !mini)
		return (NULL);
	current = mini->envvars;
	while (current != NULL)
	{
		if (strcmp(current->key, env_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*expand_env_var(char *token, t_minishell *mini)
{
	char	*expanded_token;
	char	*env_value;
	char	*env_name;

	if (token[0] != '$')
		return (token);
	env_name = ft_strdup(token + 1);
	if (!env_name)
	{
		perror("ft_strdup memory allocation failed");
		return (NULL);
	}
	env_value = get_env_value(env_name, mini);
	free(env_name);
	if (env_value)
	{
		expanded_token = ft_strdup(env_value);
		if (!expanded_token)
		{
			perror("ft_strdup failed");
			return (NULL);
		}
		return (expanded_token);
	}
	return (token);
}
