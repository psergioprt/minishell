/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:12:05 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/11 23:10:04 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	read_lines(t_minishell *mini)
{
	char	*read ;
	char	*prompt;

	prompt = "\033[1;31mminishell>\033[0m ";
	read = NULL;
	read = readline(prompt);
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
			if (!mini->has_error)
				print_nodes(mini->tokelst);
			free_list(mini);
		}
		free(read);
		read = readline(prompt);
	}
	free_list(mini);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	mini;

	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
	{
		printf("Usage: ./minishell\nDoes not accept additional arguments.\n");
		exit (1);
	}
	mini.tokelst = NULL;
	parse_env(&mini, env);
//	print_envvar(&mini);
	copy_env(env, &mini);
	read_lines(&mini);
	printf("Exiting program...\n");
	cleanup_readline();
	free_envvars(&mini);
	return (0);
}
