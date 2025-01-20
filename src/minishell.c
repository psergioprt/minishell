/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:12:05 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/20 00:32:25 by pauldos-         ###   ########.fr       */
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

void	read_lines_exit(t_minishell *mini, char *read)
{
	if (read == NULL)
	{
		write(STDOUT_FILENO, "\033[1G\033[2kexit\0\n", 15);
		free_list(mini);
		exit (0);
	}
	if (ft_strcmp(read, "exit") == 0 && !(ft_strlen(read) == 0))
	{
		write(STDOUT_FILENO, "exit\n", 5);
		free(read);
		free_list(mini);
		exit (0);
	}
}

void	read_lines(t_minishell *mini)
{
	char	*read ;

	mini->prompt = "\033[1;31mminishell>\033[0m ";
	read = NULL;
	while (1)
	{
		read = readline(mini->prompt);
		read_lines_exit(mini, read);
		if (*read)
		{
			split_and_add_commands(mini, read);
			add_history(read);
			if (!mini->has_error)
				print_nodes(mini->tokelst);
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
	mini.tokelst = NULL;
	parse_env(&mini, env);
	copy_env(env, &mini);
	read_lines(&mini);
	cleanup_readline();
	free_envvars(&mini);
	return (0);
}
