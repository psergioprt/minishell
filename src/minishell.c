/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 22:55:20 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/24 16:52:12 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

void	read_lines_exit(t_minishell *mini, char *read)
{
	if (read == NULL)
	{
		write(STDOUT_FILENO, "\033[1G\033[2kexit\0\n", 15);
		free_list(mini);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
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

void	do_commands(t_minishell *mini, char *read)
{
	split_and_add_commands(mini, read);
	add_history(read);
	if (mini->has_error)
	{
		free_list(mini);
		clear_heredoc_list(mini);
		return ;
	}
	mini->interactive = 0;
	init_sigaction(mini->interactive);
	mini->saved_stdout = dup(STDOUT_FILENO);
	mini->saved_stdin = dup(STDIN_FILENO);
	exec_cmds(mini);
	redir_or_close_saved(mini);
	free_commands(mini->commands);
	free_list(mini);
	clear_heredoc_list(mini);
	mini->interactive = 1;
	init_sigaction(mini->interactive);
}

void	read_lines(t_minishell *mini)
{
	char	*read;

	read = NULL;
	while (1)
	{
		mini->interactive = 1;
		read = readline("\033[1;31mminishell>\033[0m ");
		if (g_exit_code != 0)
		{
			mini->exit_status = g_exit_code;
			g_exit_code = 0;
		}
		read_lines_exit(mini, read);
		if (*read && is_spaces(read))
			do_commands(mini, read);
		free(read);
	}
	free_commands(mini->commands);
	free_list(mini);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	mini;

	mini.interactive = 1;
	init_sigaction(mini.interactive);
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		ft_putstr_fd("Does not accept additional arguments.\n", 2);
		exit (1);
	}
	(void)argc;
	(void)argv;
	mini.tokenlst = NULL;
	mini.exit_status = 0;
	mini.has_error = false;
	mini.i = 0;
	parse_env(&mini, env);
	copy_env(env, &mini);
	read_lines(&mini);
	free_envvars(&mini);
	return (0);
}
