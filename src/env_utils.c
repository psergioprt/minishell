/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:49:34 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/09 22:14:27 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	free_envvars(t_minishell *mini)
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
}*/

/*void	parse_env(t_minishell *mini, char *env[])
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
}*/

void parse_env(t_minishell *mini, char *env[])
{
    t_env *head = NULL;
    t_env *tail = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        // Allocate a new node
        t_env *new_node = malloc(sizeof(t_env));
        if (!new_node) {
            perror("Failed to allocate memory for envvars node");
            // Free already allocated nodes
            while (head) {
                t_env *temp = head;
                head = head->next;
                free(temp->key);
                free(temp->value);
                free(temp);
            }
            mini->envvars = NULL;
            return;
        }

        // Populate the node
        char *delimiter = strchr(env[i], '=');
        if (delimiter) {
            size_t key_len = delimiter - env[i];
            new_node->key = strndup(env[i], key_len);
            new_node->value = strdup(delimiter + 1);
            new_node->print = true;
        } else {
            new_node->key = strdup(env[i]);
            new_node->value = NULL;
            new_node->print = false;
        }
        new_node->next = NULL;

        // Append to the linked list
        if (!head) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    mini->envvars = head;
}

void copy_env(char *env[], t_minishell *mini)
{
	int	i;
	int	env_count;

	// Count the number of environment variables
	env_count = 0;
	while (env[env_count] != NULL)
		env_count++;

	// Allocate memory for envp
	mini->envp = (char **)malloc(sizeof(char *) * (env_count + 1)); // +1 for NULL terminator
	if (!mini->envp)
	{
		perror("Malloc failed for envp");
		return;
	}

	// Copy each environment variable
	i = 0;
	while (i < env_count)
	{
		mini->envp[i] = strdup(env[i]); // Allocate and copy the string
		if (!mini->envp[i])
		{
			perror("Malloc failed for envp string");
			while (--i >= 0)
				free(mini->envp[i]); //TODO: error free function
			free(mini->envp);
			return;
		}
		i++;
	}

	// Null-terminate the array
	mini->envp[env_count] = NULL;
	// separar em key e value - DONE
	// Debug print to verify copying
	//TODO: DELETE TESTES COPY ENV
	for (i = 0; i < env_count; i++)
	{
		printf("Copied env[%d]: %s\n", i, mini->envp[i]);
	}
	//TODO: DELETE TESTES COPY ENV
}
