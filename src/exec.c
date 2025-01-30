/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:35:07 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/30 08:20:36 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(t_minishell *mini)
{
	t_env	*envvars;
	char	*pathname;
	char	**paths;
	int		i;
	
	i = 0;
	envvars = mini->envvars;
	while (envvars != NULL)
	{
		if (ft_strncmp(envvars->key, "PATH", 4) == 0)
			break;
		envvars = envvars->next;
	}
	if (envvars == NULL || envvars->value == NULL)
		return (NULL);
	paths = ft_split(envvars->value, ':');
	while (paths[i])
	{	
  		pathname = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin(pathname, mini->command);
		if (access(pathname, F_OK) == 0)
			return (pathname);
		i++;
	}
	return (NULL);
}

char	*fallback_path(t_minishell *mini)
{
	char	*cwd;
	char	*full_path;

	if (mini->command[0] == '.' && mini->command[1] == '/')
	{
		cwd = getcwd(NULL, 0); // Get the current working directory
		if (!cwd)
		{
			perror("getcwd failed");
			return (NULL);
		}
		full_path = ft_strjoin(cwd, "/");
		free(cwd); // Free the allocated cwd after use
		full_path = ft_strjoin(full_path, mini->command + 2); // Skip "./"
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path); // Free if the path is invalid
	}
	return (NULL);
}



char	**get_argv(t_minishell *mini, int i, t_node *node)
{
	int		len;
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	if (!argv)
		return (NULL);
	while (node) {
		len = ft_strlen(node->token);
		argv[i] = (char *)malloc(sizeof(char) * (len + 1)); // Allocate for each string
		if (!argv[i]) {
			perror("Error allocating argv[i]");
			// Free previously allocated memory
			while (i > 0)
				free(argv[--i]);
			free(argv);
			free(mini->command);
			return (NULL);
		}
		ft_strlcpy(argv[i], node->token, len + 1);
		node = node->next;
		i++;
	}
	argv[i] = NULL; // Null-terminate argv
	
	//TODO: Depois dos testes, apagar
	// Print argv for debugging
	for (int j = 0; argv[j]; j++) {
		printf("Argv[%d]: %s\n", j, argv[j]);
	}
	return (argv);
}

void	get_command(t_minishell *mini)
{
	int		len;
	t_node	*node;

	node = mini->tokenlst; // Store the head of the list
	len = ft_strlen(node->token);
	mini->command = (char *)malloc(sizeof(char) * (len + 1));
	if (!mini->command) {
		perror("Error allocating command");
		return ;
	}
	ft_strlcpy(mini->command, node->token, len + 1);
}
//TODO: 25 linhas

/*int execute_execve(t_minishell *mini)
{
	char	**argv;
	char	*pathname;
	int	i = 0;
	int	j = 0;
	t_node  *node;

	node = mini->tokenlst;
	get_command(mini);
	t_node *current = node;
	//count number of non redirects (to allocate mem)
	while (current)
	{
		i++;
		current = current->next;
	}
	argv = malloc((i + 1) * sizeof(char *));
	if (!argv)
		ft_error("malloc failed", mini);
	// Build argv, skip redirection tokens
	current = node;
	while (current)
	{
		argv[j] = current->token;
		printf("ARGV[%d]: %s\n", j, argv[j]);
		j++;
		current = current->next;
	}
	argv[j] = NULL;
	pathname = find_path(mini);
	if (!pathname)
	{
		pathname = fallback_path(mini);
		if (!pathname)
		{
			printf("%s: command not found\n", node->token);
			return (-1);
		}
	}
	printf("Executing command with execve: %s\n", pathname);
	// Debug
	printf("Pathname: %s\n", pathname); //TODO: Remove debug print
	printf("Command: %s\n", mini->command); //TODO: Remove debug print
	// Execute the command using execve
	if (execve(pathname, argv, mini->envp) == -1)
		ft_error("execve failed!", mini);
	printf("Executing execve with pathname: %s\n", pathname);
    // Free the memory allocated for argv (for testing purposes)
    	for (int k = 0; argv[k]; k++)
	{
		free(argv[k]);
	}
	free(argv);
	free(mini->command);
	return (1);
}*/


int	execute_execve(t_minishell *mini) 
{
	// Variable declarations
	char	**argv;
	char	*pathname;
	int		i;
	t_node	*node;

	node = mini->tokenlst; // Store the head of the list
	// Allocate and copy command
	get_command(mini);
	// Count the number of tokens
	i = count_node(mini);
	argv = get_argv(mini, i, node);
	if (!argv)
		ft_error("Couldnt get argv!", mini);
	pathname = find_path(mini);
	if (!pathname)
	{
		pathname = fallback_path(mini);
		if (!pathname)
		{
			printf("%s: command not found\n", node->token);
			//ft_error("Couldn't find path!", mini);
			return (-1);
		}
	}
	printf("Pathname: %s\n", pathname); //TODO: Apagar teste find_path
	printf("Command: %s\n", mini->command); //TODO: Apagar teste find_path
	if (execve(pathname, argv, mini->envp) == -1) //TODO: Fazer o fork
		ft_error("execve failed!", mini);
	// Free argv for testing purposes
	for (int j = 0; argv[j]; j++) {
		free(argv[j]);
	}
	free(argv);
	free(mini->command);
	return (1);
}
