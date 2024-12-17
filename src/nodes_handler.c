/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:48:55 by pauldos-          #+#    #+#             */
/*   Updated: 2024/12/17 20:02:06 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*create_command_node(const char *command)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		perror("Error!\nFailed to allocate memory for new_node\n");
		return (NULL);
	}
	new_node->command = ft_strdup(command);
	new_node->next = NULL;
	return (new_node);
}

//function created to add commands to linked list
void	add_command_node(t_node **list, const char *command)
{
	t_node		*new_node;
	t_node		*current;
	static int	node_index = 0;

	node_index = 1;
new_node = create_command_node(command);
	if (!new_node)
		return ;
	if (!*list)
	{
		//printf("Node[head]: %s\n", command);
		*list = new_node;
	}
	else
	{
		current = *list;
		while (current->next)
		{
			current = current->next;
			node_index++;
		}
		current->next = new_node;
		//printf("Node[%d]: %s\n", node_index++, command);
	}
}

//function created to check delimeters characters
static int	is_delimeter(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

void split_and_add_commands(t_node **list, const char *input)
{
		int	i;
		int	j;
	char	current_token[1024];
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote && input[i] == ' ')
		{
			if (input[i + 1] == ' ' || input[i + 1] == '"' || input[i + 1] == '\'')
			{
				i++;
				continue;
			}
			if (j > 0) // Add the current token if not empty
			{
				current_token[j] = '\0';
				add_command_node(list, current_token);
				j = 0;
			}
		}
		else if (!quote && (input[i] == '>' || input[i] == '<'))
		{
			if (j > 0) // Add the current token if not empty
			{
				current_token[j] = '\0';
				add_command_node(list, current_token);
				j = 0;
			}
			if (input[i + 1] == input[i])
			{
				char double_op[3] = {input[i], input[i + 1], '\0'};
				add_command_node(list, double_op);
				i++;
			}
			else
			{
				char single_op[2] = {input[i], '\0'};
				add_command_node(list, single_op);
			}
		}
		else if (!quote && input[i] == '|')
		{
			if (j > 0) // Add the current token if not empty
			{
				current_token[j] = '\0';
				add_command_node(list, current_token);
				j = 0;
			}
			char delimiter[2] = {input[i], '\0'};
			add_command_node(list, delimiter);
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!quote)
			{
				quote = input[i];
				i++;
				while (input[i] && input[i] != quote)
					current_token[j++] = input[i++];
				if (input[i] == quote)
					quote = 0;
				else
				{
					printf("Error: Unclosed quote detected!\n");
					return;
				}
			}
		}
		else
			current_token[j++] = input[i];
		i++;
	}
	if (j > 0)
	{
		current_token[j] = '\0';
		add_command_node(list, current_token);
	}
}

char    *ft_strtok(char *str, const char *delim)
{
	static char *cur = NULL;
	char	*token_start;
	char	*result;

	if (str != NULL)
		cur = str;
	if (cur == NULL || *cur == '\0')
		return (NULL);
	while (*cur && is_delimeter(*cur, delim))
		cur++;
	if (*cur == '\0')
		return (NULL);
	token_start = cur;
	while (*cur && !is_delimeter(*cur, delim))
		cur++;
	if (*cur)
		*cur++ = '\0';
	result = ft_strdup(token_start);
	return (result);
}

//function created to free the linked list
void	free_list(t_node *list)
{
	t_node	*current;

	while (list)
	{
		current = list;
		list = list->next;
		free(current->command);
		free(current);
	}
}
