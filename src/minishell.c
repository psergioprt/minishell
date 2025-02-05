/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:57:45 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/05 08:18:03 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

//TODO isto e desnecessario com o comando exit

void check_open_fds()
{
    for (int fd = 0; fd < 256; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            printf("File descriptor %d is still open\n", fd);
        }
    }
}

void	read_lines_exit(t_minishell *mini, char *read)
{
	if (read == NULL)
	{
		write(STDOUT_FILENO, "\033[1G\033[2kexit\0\n", 15);
		free_list(mini);
		cleanup_fd(mini);
		check_open_fds();
		exit (0);
	}
	if (ft_strcmp(read, "exit") == 0 && !(ft_strlen(read) == 0))
	{
		write(STDOUT_FILENO, "exit\n", 5);
		free(read);
		free_list(mini);
		cleanup_fd(mini);
		check_open_fds();
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
		read = readline("\033[1;31mminishell>\033[0m ");
		if (g_exit_code == 130)
		{
			mini->exit_status = 130;
			g_exit_code = 0;
		}
		read_lines_exit(mini, read);
		if (*read && is_spaces(read))
		{
			split_and_add_commands(mini, read);
			add_history(read);
			if (!mini->has_error)
				print_nodes(mini->tokenlst);
			if (mini->has_error)
			{
				free(read);
				free_list(mini);
				clear_heredoc_list(mini);
				continue ;
			}
			mini->saved_stdout = dup(STDOUT_FILENO);
			mini->saved_stdin = dup(STDIN_FILENO);
			first_token(mini);
			dup2(mini->saved_stdout, STDOUT_FILENO);
			dup2(mini->saved_stdin, STDIN_FILENO);
			close(mini->saved_stdout);
			close(mini->saved_stdin);
			free_list(mini);
			clear_heredoc_list(mini);
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
