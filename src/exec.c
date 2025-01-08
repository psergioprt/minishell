/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:35:07 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/08 10:53:05 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(t_minishell *mini)
{
	int		i;
	char	*pathname;
	char	**paths;
	
	i = 0;
	while (ft_strncmp(mini->envvars[i].key, "PATH", 4) != 0)
		i++;
	paths = ft_split(mini->envvars[i].value, ':');
	i = 0;
	while (paths[i])
	{	
  		pathname = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin(pathname, mini->command);
		if (access(pathname, F_OK) == 0)
			return (pathname);
		i++;
	}
	return ("error");
}

int	count_node(t_minishell *mini)
{
	int		i;
	t_node	*temp;

	i = 0;
	temp = mini->tokenlst; // Temporary pointer for counting
	while (temp) {
		i++;
		temp = temp->next;
	}
	return (i);
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
		ft_error("Couldn't find path!", mini);
	printf("Pathname: %s\n", pathname); //TODO: Apagar teste find_path
	printf("Command: %s\n", mini->command); //TODO: Apagar teste find_path
	if (execve(pathname, argv, mini->envp) == -1) //TODO: Fazer o fork
		ft_error("execve failed!", mini);
	// Free argv for testing purposes
	for (int j = 0; argv[j]; j++) {
		free(argv[j]);
	}
	free(argv);
	//free(mini->command);
	return (1);
}

