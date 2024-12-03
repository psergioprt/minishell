/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:48:55 by pauldos-          #+#    #+#             */
/*   Updated: 2024/12/03 23:25:16 by pauldos-         ###   ########.fr       */
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
	static int	node_index;

	node_index = 1;
	new_node = create_command_node(command);
	if (!new_node)
		return ;
	if (!*list)
	{
		printf("Node[head]: %s\n", command);
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
		printf("Node[%d]: %s\n", node_index++, command);
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

//function created to tokenize string elements

/*char	*handle_signs(char *cur, const char *delim)
{
	char		double_char[3];
	char		single_char[2];
	
	while (*cur && is_delimeter(*cur, delim))
	{
		if (*cur == '|')
		{
			cur++;
			return (ft_strdup("|"));
		}
		else if ((*cur == '>' && *(cur + 1) == '>') || \
				(*cur == '<' && *(cur + 1) == '<'))
		{
			double_char[0] = *cur;
			double_char[1] = *(cur + 1);
			double_char[2] = '\0';
			cur += 2;
			return (ft_strdup(double_char));
		}
		else if (*cur == '>' || *cur == '<')
		{
			single_char[0] = *cur;
			single_char[1] = '\0';
			cur++;
			return (ft_strdup(single_char));
		}
		else
			cur++;
	}
	return ("hi");
}*/

char	*ft_strtok(char *str, const char *delim)
{
	static char	*cur = NULL;
	char		*token_start;
	char		double_char[3];
	char		single_char[2];
	char		quote;

	if (str != NULL)
		cur = str;
	if (cur == NULL)
		return (NULL);
	//handle_signs(cur, delim);
	while (*cur && is_delimeter(*cur, delim))
	{
		if (*cur == '|')
		{
			cur++;
			return (ft_strdup("|"));
		}
		else if ((*cur == '>' && *(cur + 1) == '>') || \
				(*cur == '<' && *(cur + 1) == '<'))
		{
			double_char[0] = *cur;
			double_char[1] = *(cur + 1);
			double_char[2] = '\0';
			cur += 2;
			return (ft_strdup(double_char));
		}
		else if (*cur == '>' || *cur == '<')
		{
			single_char[0] = *cur;
			single_char[1] = '\0';
			cur++;
			return (ft_strdup(single_char));
		}
		else
			cur++;
	}
	if (*cur == '\0')
		return (NULL);
	token_start = cur;
	char		*start_quote;
	size_t		len;
	char		*quoted_token;
	while (*cur && !is_delimeter(*cur, delim))
	{
		if (*cur == '\\')
			cur += 2;
		else if (*cur == '"' || *cur == '\'')
		{
			start_quote = cur;
			quote = *cur++;
			while (*cur && *cur != quote)
				cur++;
			if (*cur == '\0')
				return ("Non closed quotes");
			if (*cur)
				cur++;
			len = cur - start_quote;
			quoted_token = ft_substr(start_quote, 0, len);
			return (quoted_token);
		}
		else
			cur++;
	}
	if (*cur)
	{
		*cur = '\0';
		cur++;
	}
	return (token_start);
}

//function created to split each command from an input
void	split_and_add_commands(t_node **list, const char *input)
{
	char	*token;
	char	*delimeters;
	char	*input_copy;

	delimeters = "| < >";
	input_copy = ft_strdup(input);
	free_list(*list);
	*list = NULL;
	token = ft_strtok(input_copy, delimeters);
	while (token != NULL)
	{
		add_command_node(list, token);
		token = ft_strtok(NULL, delimeters);
	}
	free(input_copy);
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
