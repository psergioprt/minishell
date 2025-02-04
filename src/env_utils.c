/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:49:34 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/04 18:01:34 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

t_env	*create_env_node(char *env)
{
	t_env	*new_node;
	char	*delimiter;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	delimiter = strchr(env, '=');
	if (delimiter)
	{
		new_node->key = strndup(env, delimiter - env);
		new_node->value = strdup(delimiter + 1);
		new_node->print = true;
	}
	else
	{
		new_node->key = strdup(env);
		new_node->value = NULL;
		new_node->print = false;
	}
	new_node->next = NULL;
	return (new_node);
}

void	parse_env(t_minishell *mini, char *env[])
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;

	i = 0;
	head = NULL;
	tail = NULL;
	while (env[i])
	{
		new_node = create_env_node(env[i++]);
		if (!new_node)
		{
			perror("Failed to allocate memory for envvars node");
			free_env_list(head);
			mini->envvars = NULL;
			return ;
		}
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
	}
	mini->envvars = head;
}

void	free_envp(int i, t_minishell *mini)
{
	while (--i >= 0)
		free(mini->envp[i]);
	free(mini->envp);
}

void	copy_env(char *env[], t_minishell *mini)
{
	int	i;
	int	env_count;

	env_count = 0;
	while (env[env_count] != NULL)
		env_count++;
	mini->envp = (char **)malloc(sizeof(char *) * (env_count + 1));
	if (!mini->envp)
	{
		perror("Malloc failed for envp");
		return ;
	}
	i = 0;
	while (i < env_count)
	{
		mini->envp[i] = strdup(env[i]);
		if (!mini->envp[i])
		{
			perror("Malloc failed for envp string");
			free_envp(i, mini);
			return ;
		}
		i++;
	}
	mini->envp[env_count] = NULL;
}
