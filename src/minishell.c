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

void	print_nodes(t_node *command_list)
{
	int		i;
	t_node	*current;

	i = 0;
	current = command_list;
	while (current)
	{
		if (i == 0)
			printf("\033[1;33mNode[0]: %s\033[0m\n", current->token);
		else
			printf("\033[1;33mNode[%d]: %s\033[0m\n", i, current->token);
		current = current->next;
		i++;
	}
}
//TODO isto e desnecessario com o comando exit
void	read_lines_exit(t_minishell *mini, char *read)
{
	if (read == NULL)
	{
		write(STDOUT_FILENO, "\033[1G\033[2kexit\0\n", 15);
		free_list(mini);
		exit (0);
	}
/* 	if (ft_strcmp(read, "exit") == 0 && !(ft_strlen(read) == 0))
	{
		write(STDOUT_FILENO, "exit\n", 5);
		free(read);
		free_list(mini);
		exit (0);
	} */
}

bool	is_spaces(char *read)
{
	int	i;
	
	i = 0;
	while (read[i])
	{
		if (read[i] != ' ' && !(read[i] >= 9 && read[i] <= 13))
			return (true);
		i++;
	}
	return (false);
}

void	read_lines(t_minishell *mini)
{
	char	*read;

	read = NULL;
	while (1)
	{
		read = readline("\033[1;31mminishell>\033[0m ");
		read_lines_exit(mini, read); //TODO da segfault quando comentada no cntrl D	
		if (*read && is_spaces(read))
		{
			split_and_add_commands(mini, read);
			add_history(read);
			if (!mini->has_error)
				print_nodes(mini->tokenlst);
			if (mini->has_error)
			{
				free(read);
				free_list(mini);
				continue ;
			}
			first_token(mini);
			free_list(mini);
		}
		free(read);
	}
	free_list(mini);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	mini;

	init_sigaction();
	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
	{
		printf("Usage: ./minishell\nDoes not accept additional arguments.\n");
		exit (1);
	}
	mini.tokenlst = NULL;
	mini.exit_status = 0;
	parse_env(&mini, env);
	copy_env(env, &mini);
	read_lines(&mini);
	cleanup_readline();
	free_envvars(&mini);
	return (0);
}


//TODO: Apagar main antiga
/* int	main(int argc, char *argv[], char *env[]) //env[]: Environment variables ... KEY=VALUE That will be used with the entered command
{
	char	*read;
	t_minishell	*data;
	t_node	*current;
	
	
	(void)argc;
	(void)argv;
	data = NULL;
	//TODO: Tem de inicializar antes de fazer isto - falar com paulo 
	//data = create_command_node("dummy_command");
	data = malloc(sizeof(t_node));
	copy_env(env, data);
	parse_env(data, env);
	//TODO: DELETE TESTES SPLIT PARSE ENV
	 // Print the parsed environment variables
	if (data->envvars) {
		for (int i = 0; data->envvars[i].key != NULL; i++) {
			printf("Key: %s, Value: %s, Print: %d\n",
				data->envvars[i].key,
				data->envvars[i].value ? data->envvars[i].value : "(null)",
				data->envvars[i].print);
		}
		//JA PASSOU AQUI SEG FAULT
		// Free the allocated memory
		for (int i = 0; data->envvars[i].key != NULL; i++) {
			//free(data->envvars[i].key);
			//free(data->envvars[i].value);
		} 
		//JA PASSOU AQUI SEG FAULT
		//free(data->envvars);
	}
	//TODO: DELETE TESTES SPLIT PARSE ENV 
	//LOOP TO ADD EACH COMMAND TO NODES
	while ((read = readline("minishell> ")) != NULL)
	{
		if (ft_strcmp(read, "exit") == 0)
			break;
		if (*read)
		{
			split_and_add_commands(&data, read);
			add_history(read);
			first_token(data);
		}
		free(read);
	}
	

	//LOOP TO ADD INPUT LINES TO NODES
	while ((read = readline("minishell> "))!= NULL)
	{
		if (ft_strcmp(read, "time to leave minishell") == 0)
			break ;
		if (*read)
		{                                                                                                                                                                                                                                                                     
			add_command_node(&minishell, read);
			add_history(read); //from readline/history.h ... manages history (scrolls inputed commands)
			printf("command: %s\n", read);
		}
		free(read);
	}
	current = data;
	//LOOP TO OUTPUT NODES VALUES, AS SOON AS EITHER CTRL + D IS PRESSED OR THE MESSAGE:
	//"time to leave minishell" IS ENTERED
	

	int	i = 0;
	while (current)
	{
		if (i == 0)
			printf ("Nodes command list: node[head]: %s\n", current->token);

		else
			printf ("Nodes command list: node[%d]: %s\n", i, current->token);
		current = current->next;
		i++;
	}
	free_list(data);
	return (0);
}
 */