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
	
	(void)argc;
	(void)argv;
	print_env(env);
	while (1)
	{
		read = readline("minishell$> "); //readline from readline/readline.h ... allows command entry, edit and history.
						 //readline must be installed for usage: sudo apt-get install libreadline-dev
		if (!read)
		{
			printf("\n");
			break ;
		}
		printf("Readline output just to verify: %s\n", read);
		add_history(read); //from readline/history.h ... manages history (scrolls inputed commands)
		free(read);
	}
	return (0);
}
