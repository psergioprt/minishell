#include "../include/minishell.h"

//function created to create nodes
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
//function created to add commands to linked list
void	add_command_node(t_env_node **list, const char *command)
{
	t_env_node	*new_node;
	t_env_node	*current;

	new_node = create_command_node(command);
	if (!new_node)
		return ;
	if (!*list)
	{
		printf("Point 2: %s\n", command);
		*list = new_node;
	}
	else
	{
		printf("Point 3: %s\n", command);
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_node;
		printf("added command to list: %s\n", command);
	}
}
//function created to split each command from an input
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
//function created to free the linked list
void	free_list(t_env_node *list)
{
	t_env_node	*current;
	while (list)
	{
		current = list;
		list = list->next;
		free(current->command);
		free(current);
	}
}
