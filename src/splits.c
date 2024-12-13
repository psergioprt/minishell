/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:00:32 by jcavadas          #+#    #+#             */
/*   Updated: 2024/12/12 19:34:45 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void parse_env(t_node *node, char *env[])
{
	int count = 0;

	// Count the number of environment variables
	while (env[count] != NULL) {
		count++;
	}

	// Allocate memory for the envvars array in the node
	node->envvars = malloc(sizeof(t_env) * count);
	if (!node->envvars) {
		perror("Failed to allocate memory for envvars");
		return;
	}

	for (int i = 0; i < count; i++) {
		char *delimiter = strchr(env[i], '=');
		if (delimiter) {
			// Split the string into key and value
			size_t key_len = delimiter - env[i];
			size_t value_len = strlen(delimiter + 1);

			node->envvars[i].key = malloc(key_len + 1);
			node->envvars[i].value = malloc(value_len + 1);

			if (!node->envvars[i].key || !node->envvars[i].value) {
				perror("Failed to allocate memory for key or value");
				// Free previously allocated memory
				for (int j = 0; j < i; j++) {
					free(node->envvars[j].key);
					free(node->envvars[j].value);
				}
				free(node->envvars);
				node->envvars = NULL;
				return;
			}

			strncpy(node->envvars[i].key, env[i], key_len);
			node->envvars[i].key[key_len] = '\0';
			strcpy(node->envvars[i].value, delimiter + 1);
			node->envvars[i].print = true; // Default to print being true
		} else {
			// Handle the case where there's no '='
			node->envvars[i].key = strdup(env[i]);
			node->envvars[i].value = NULL;
			node->envvars[i].print = false;
		}
	}
	node->envvars[count].key = NULL;
	node->envvars[count].value = NULL;
	node->envvars[count].print = false;
}

void copy_env(char *env[], t_node *data)
{
	int	i;
	int	env_count;

	// Count the number of environment variables
	env_count = 0;
	while (env[env_count] != NULL)
		env_count++;

	// Allocate memory for envp
	data->envp = (char **)malloc(sizeof(char *) * (env_count + 1)); // +1 for NULL terminator
	if (!data->envp)
	{
		perror("Malloc failed for envp");
		return;
	}

	// Copy each environment variable
	i = 0;
	while (i < env_count)
	{
		data->envp[i] = strdup(env[i]); // Allocate and copy the string
		if (!data->envp[i])
		{
			perror("Malloc failed for envp string");
			while (--i >= 0)
				free(data->envp[i]); //TODO: error free function
			free(data->envp);
			return;
		}
		i++;
	}

	// Null-terminate the array
	data->envp[env_count] = NULL;
	// separar em key e value - DONE
	// Debug print to verify copying
	//TODO: DELETE TESTES COPY ENV
	for (i = 0; i < env_count; i++)
	{
		printf("Copied env[%d]: %s\n", i, data->envp[i]);
	}
	//TODO: DELETE TESTES COPY ENV
}


