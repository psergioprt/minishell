/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:35:07 by jcavadas          #+#    #+#             */
/*   Updated: 2024/12/20 12:41:23 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(t_minishell *data)
{
	int		i;
	char	*pathname;
	char	**paths;
	
	i = 0;
	while (ft_strncmp(data->envvars[i].key, "PATH", 4) != 0)
		i++,
	paths = ft_split(data->envvars[i].value, ':');
	i = 0;
	while (paths[i++])
	{
		pathname = ft_strjoin(paths[i], '/' + data->command); //TODO fazer join com o comando tambem ex:ls
		if (access(pathname, F_OK) == 0)
			return (pathname);
	}
	return ("error");
}




int	execute_execve(t_minishell *data)
{
	// Variable declarations
	char	**argv;
	int		len;
	int		i;
	t_node	*node;
	t_node	*temp;

	// Initialize variables
	i = 0;
	node = data->tokenlst; // Store the head of the list
	temp = data->tokenlst; // Temporary pointer for counting

	// Allocate and copy command
	len = ft_strlen(node->token);
	data->command = (char *)malloc(sizeof(char) * (len + 1)); // Allocate correctly
	if (!data->command) {
		perror("Error allocating command");
		return (-1);
	}
	ft_strlcpy(data->command, node->token, len + 1);

	// Count the number of tokens
	while (temp) {
		i++;
		temp = temp->next;
	}

	// Allocate memory for argv (i + 1 for NULL terminator)
	argv = (char **)malloc(sizeof(char *) * (i + 1));
	if (!argv) {
		perror("Error allocating argv");
		free(data->command); // Free previously allocated memory
		return (-1);
	}

	// Populate argv
	i = 0;
	while (node) {
		len = ft_strlen(node->token);
		argv[i] = (char *)malloc(sizeof(char) * (len + 1)); // Allocate for each string
		if (!argv[i]) {
			perror("Error allocating argv[i]");
			// Free previously allocated memory
			while (i > 0)
				free(argv[--i]);
			free(argv);
			free(data->command);
			return (-1);
		}
		ft_strlcpy(argv[i], node->token, len + 1);
		node = node->next;
		i++;
	}
	argv[i] = NULL; // Null-terminate argv

	// Print argv for debugging
	for (int j = 0; argv[j]; j++) {
		printf("Argv[%d]: %s\n", j, argv[j]);
	}

	// Free argv for testing purposes
	for (int j = 0; argv[j]; j++) {
		free(argv[j]);
	}
	free(argv);
	//free(data->command);

	return (1);
}



































/* 
int	execute_execve(t_minishell *data)
{
	//TODO: fazer a cena de antes de fazer o execve
	// dar split no $PATH nos ':'
	//char	*pathname;
	char	**argv;
	int		len;
	int		i;
	t_node	*node;
	t_node	*temp;

	temp = data->tokenlst;

	i = 0;
	len = ft_strlen(data->tokenlst->token); //TODO: mudar toda a logica para ficar com a nova struct
	data->command = (char *)malloc(sizeof(char *) * (len + 1));

	ft_bzero(data->command, len);
	ft_strlcpy(data->command, data->tokenlst->token, len + 1);

	//TODO: transformar todos os tokens/argumentos da funcao num array argv[]

	printf("data->command: %s\n", data->command);
	//TODO: segfault em baixo
	while (data->tokenlst->next)
	{
		i++;
		data->tokenlst = data->tokenlst->next;
	}
	printf("UWU\n");
	argv = (char **)malloc(sizeof(char *) * (i + 1));
	if (!argv)
		return(-1);
	node = data->tokenlst;
	while (temp->next != NULL) //TODO: nao esta a entrar aqui
	{
		printf("OwO");
		len = ft_strlen(node->token);
		ft_strlcpy(argv[i++], node->token, len);
		node = node->next;
	}
	printf("ERROR\n");
	argv[i] = '\0';

	
	//TODO: apagar testes argv
	i = 0;
	
	while (argv[i++] != NULL)
	{
		printf("UWU\n");
		printf("Argv[%d]: %s\n", i, argv[i]);
	}
	//TODO: apagar testes argv


	
	//TODO: testar se esta a ficar todos os argumentos em argv para o execve
	//pathname = find_path(data);
	
	//printf("Pathname: %s\n", pathname); //TODO: Apagar teste find_path

	printf("ERROR2\n"); //TODO: esta a seg faultar aqui	
	//TODO: testar find_path
	return (1);
}
 */