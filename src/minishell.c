/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:12:05 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/07 12:49:55 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * Function to print environment variables
 * 	void	print_env(char *env[])
 * 
 * Function created to handle readline exit
 * 	ft_strcmp(char *str1, char *str2)
 * 
 * *env[]: Environment variables ... 
 * 	KEY=VALUE will be used with the entered command
 * 	add in main -> print_env(env); to print the environment variables
 *
 * LOOP TO ADD EACH COMMAND TO NODES
 *	while ((read = readline("minishell> ")) != NULL)
 */
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

void	print_envvar(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->envvars[i].key != NULL)
	{
		printf("Key: %s, Value: %s, Print: %d\n", mini->envvars[i].key, \
				mini->envvars[i].value, mini->envvars[i].print);
		i++;
	}
}

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

void	print_nodes(t_node *command_list)
{
	int		i;
	t_node	*current;

	i = 0;
	current = command_list;
	while (current)
	{
		if (i == 0)
			printf("Node[head]: %s\n", current->token);
		else
			printf("Node[%d]: %s\n", i, current->token);
		current = current->next;
		i++;
	}
}

void	read_lines(t_minishell *mini)
{
	char	*read;

	read = NULL;
	read = readline("minishell> ");
	while (read != NULL)
	{
		if (ft_strcmp(read, "exit") == 0)
		{
			free(read);
			free_list(mini);
			break ;
		}
		if (*read)
		{
			split_and_add_commands(mini, read);
			add_history(read);
			print_nodes(mini->tokelst);
			free_list(mini);
		}
		free(read);
		read = readline("minishell> ");
	}
	free_list(mini);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	mini;

	(void)argc;
	(void)argv;
//	(void)env;
	if (argc != 1 || argv[1])
	{
		printf("Usage: ./minishell\nDoes not accept additional arguments.\n");
		exit (1);
	}
	mini.tokelst = NULL;
	parse_env(&mini, env);
	print_envvar(&mini);
	//copy_env(env, &mini);
	read_lines(&mini);
	printf("Exiting program...\n");
	cleanup_readline();
	free_envvars(&mini);
	return (0);
}
