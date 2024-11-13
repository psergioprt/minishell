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
//function created to handle readline exit
int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 - *str2 < 0)
			return (-1);
		else if (*str1 - *str2 > 0)
			return (1);
		str1++;
		str2++;
	}
	return (0);
}
int	main(int argc, char *argv[], char *env[]) //*env[]: Environment variables ... KEY=VALUE That will be used with the entered command
{
	char	*read;
	t_env_node	*command_list;
	t_env_node	*current;
	
	
	(void)argc;
	(void)argv;
	command_list = NULL;
	print_env(env);
	//LOOP TO ADD EACH COMMAND TO NODES
	while ((read = readline("minishell> ")) != NULL)
	{
		if (ft_strcmp(read, "time to leave minishell") == 0)
			break;
		if (*read)
		{
			split_and_add_commands(&command_list, read);
			add_history(read);
		}
		free(read);
	}
	//LOOP TO ADD INPUT LINES TO NODES
	/*while ((read = readline("minishell> "))!= NULL)
	{
		if (ft_strcmp(read, "time to leave minishell") == 0)
			break ;
		if (*read)
		{
			add_command_node(&command_list, read);
			add_history(read); //from readline/history.h ... manages history (scrolls inputed commands)
			printf("command: %s\n", read);
		}
		free(read);
	}*/
	current = command_list;
	//LOOP TO OUTPUT NODES VALUES, AS SOON AS EITHER CTRL + D IS PRESSED OR THE MESSAGE:
	//"time to leave minishell" IS ENTERED
	while (current)
	{
		printf ("Command while loop: %s\n", current->command);
		current = current->next;
	}
	free_list(command_list);
	return (0);
}
