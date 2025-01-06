/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:00:32 by jcavadas          #+#    #+#             */
/*   Updated: 2024/12/19 14:44:49 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void parse_env(t_minishell *mini, char *env[])
{
	int count = 0;

	// Count the number of environment variables
	while (env[count] != NULL) {
		count++;
	}

	// Allocate memory for the envvars array in the node
	mini->envvars = malloc(sizeof(t_env) * count);
	if (!mini->envvars) {
		perror("Failed to allocate memory for envvars");
		return;
	}
	//TODO trocar de for
	for (int i = 0; i < count; i++) {
		char *delimiter = strchr(env[i], '=');
		if (delimiter) {
			// Split the string into key and value
			size_t key_len = delimiter - env[i];
			size_t value_len = strlen(delimiter + 1);

			mini->envvars[i].key = malloc(key_len + 1);
			mini->envvars[i].value = malloc(value_len + 1);

			if (!mini->envvars[i].key || !mini->envvars[i].value) {
				perror("Failed to allocate memory for key or value");
				// Free previously allocated memory
				for (int j = 0; j < i; j++) {
					free(mini->envvars[j].key);
					free(mini->envvars[j].value);
				}
				free(mini->envvars);
				mini->envvars = NULL;
				return;
			}

			strncpy(mini->envvars[i].key, env[i], key_len);
			mini->envvars[i].key[key_len] = '\0';
			strcpy(mini->envvars[i].value, delimiter + 1);
			mini->envvars[i].print = true; // Default to print being true
		} else {
			// Handle the case where there's no '='
			mini->envvars[i].key = strdup(env[i]);
			mini->envvars[i].value = NULL;
			mini->envvars[i].print = false;
		}
	}
	mini->envvars[count].key = NULL;
	mini->envvars[count].value = NULL;
	mini->envvars[count].print = false;
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


