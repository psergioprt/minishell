/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:12:05 by pauldos-          #+#    #+#             */
/*   Updated: 2024/12/17 20:03:44 by pauldos-         ###   ########.fr       */
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
 *
 *
 *
 *
 *
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
			printf("Node[head]: %s\n", current->command);
		else
			printf("Node[%d]: %s\n", i, current->command);
		current = current->next;
		i++;
	}
}

void	read_lines(t_node **command_list)
{
	char	*read;

	read = readline("minishell> ");
	while (read != NULL)
	{
		if (ft_strcmp(read, "minishell") == 0)
			break ;
		if (*read)
		{
			split_and_add_commands(command_list, read);
			add_history(read);
			print_nodes(*command_list);
			free_list(*command_list);
			*command_list = NULL;
		}
		free(read);
		read = readline("minishell> ");
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_node	*command_list;

	(void)argc;
	(void)argv;
	(void)env;
	command_list = NULL;
	read_lines(&command_list);
	printf("Exiting program...\n");
	return (0);
}
