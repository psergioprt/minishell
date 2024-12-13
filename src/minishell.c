#include "../include/minishell.h"

//function to print enviornment variables


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
	t_node	*data;
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
	/*while ((read = readline("minishell> "))!= NULL)
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
	}*/
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
