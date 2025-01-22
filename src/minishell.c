/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:15:34 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/22 20:34:23 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*g_in_prompt = NULL;

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
//TODO isto e desnecessario com o comando exit
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

bool	is_spaces(char *read)
{
	int	i;

	i = 0;
	while (read[i])
	{
		if (read[i] != ' ' && !(read[i] >= 9 && read[i] <= 13))
			return (true);
		i++;
	}
	return (false);
}

void	read_lines(t_minishell *mini)
{
	char	*read;
	read = NULL;
	while (1)
	{	
		g_in_prompt =(void *)mini;
		read = readline("\033[1;31mminishell>\033[0m ");
		g_in_prompt = NULL;
		read_lines_exit(mini, read);
		if (*read && is_spaces(read))
		{
			split_and_add_commands(mini, read);
			add_history(read);
		if (!mini->has_error && g_in_prompt != NULL)
				print_nodes(mini->tokenlst);
			if (mini->has_error)
			{
				free(read);
				free_list(mini);
				continue ;
			}
			first_token(mini);
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
	mini.tokenlst = NULL;
	mini.exit_status = 0;
	parse_env(&mini, env);
	copy_env(env, &mini);
	read_lines(&mini);
	cleanup_readline();
	free_envvars(&mini);
	return (0);
}
