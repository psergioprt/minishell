#include "../include/minishell.h"

t_env_node *create_command_node(const char *command)
{
	t_env_node	*new_node;
	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
	{
		perror("Error!\nFailed to allocate memory for new_node\n");
		return (NULL);
	}
	new_node->command = ft_strdup(command);
	new_node->next = NULL;
	return (new_node);
}

void	add_command_node(t_env_node **head, const char *command)
{
	t_env_node	*new_node;
	t_env_node	*temp;

	new_node = create_command_node(command);
	if (!new_node)
		return ;
	if (!*head)
	{
		printf("Point 2: %s\n", command);
		*head = new_node;
	}
	else
	{
		printf("Point 3: %s\n", command);
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		printf("added command to list: %s\n", command);
	}
}

void	split_and_add_commands(t_env_node **head, const char *input)
{
	char	*token;
	char	*input_copy = strdup(input);

	free_list(*head);
	*head = NULL;

	token = strtok(input_copy, " ");
	while (token != NULL)
	{
		add_command_node(head, token);
		token = strtok(NULL, " ");
	}
	free(input_copy);
}

void	free_list(t_env_node *head)
{
	t_env_node	*temp;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->command);
		free(temp);
	}
}
