/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:49:37 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/10 00:09:54 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdint.h>

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
	printf("env_name after assignement, %s\n", env_name);
	if (!env_name)
	{
		perror("ft_strdup memory allocation failed");
		return (NULL);
	}
	env_value = get_env_value(env_name, mini);
	printf("env_value after assignement: %s\n", env_value);
	free(env_name);
	if (env_value)
	{
		expanded_token = ft_strdup(env_value);
		printf("expanded_token after assignment: %s\n", expanded_token);
		if (!expanded_token)
		{
			perror("ft_strdup failed");
			return (NULL);
		}
		printf("Just before returning expanded_token: %s\n", expanded_token);
		return (expanded_token);
	}
	return (token);
}
