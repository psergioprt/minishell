/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:19:35 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/27 14:19:35 by jcavadas         ###   ########.fr       */
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

int execpath_error(char *path)
{
	struct stat path_stat;

	if (ft_strchr(path, '/') || path[0] == '.')
	{
		if (access(path, F_OK) < 0) // Check if the file exists
		{
			printf("No such file or directory\n");
			return (127);
		}
		if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) // Check if it's a directory
		{
			printf("Is a directory\n");
			return (126);
		}
		if (access(path, X_OK) < 0) // Check if the file is executable
		{
			printf("Permission denied\n");
			return (126);
		}
	}
	return (0); // No error
}
