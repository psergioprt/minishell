/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:00:32 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/10 11:42:15 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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


