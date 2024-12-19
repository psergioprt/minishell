/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:12:05 by pauldos-          #+#    #+#             */
/*   Updated: 2024/12/18 18:51:22 by pauldos-         ###   ########.fr       */
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

	read = readline("minishell> ");
	while (read != NULL)
	{
		if (ft_strcmp(read, "minishell") == 0)
			break ;
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
	(void)env;
	mini.tokelst = NULL;
	read_lines(&mini);
	printf("Exiting program...\n");
	return (0);
}
