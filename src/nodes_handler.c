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
}
