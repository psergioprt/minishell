#include "../include/minishell.h"

void	print_env(char *env[])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
int	main(int argc, char *argv[], char *env[]) //*env[]: Environment variables ... KEY=VALUE That will be used with the entered command

{
	char	*read;
	t_env_node	*command_list = NULL;
	t_env_node	*current;
	
	(void)argc;
	(void)argv;
	//command_list = NULL;
	print_env(env);
	while ((read = readline("minishell> ")) != NULL)
	{
		if (*read)
		{
			add_command_node(&command_list, read);
			add_history(read); //from readline/history.h ... manages history (scrolls inputed commands)
			printf("command: %s\n", read);
		}
		free(read);
	}
	current = command_list;
	while (current)
	{
		printf ("Command: %s\n", current->command);
		current = current->next;
	}
	free_list(command_list);
	return (0);
}
