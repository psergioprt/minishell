/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:35:07 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/24 16:50:51 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	cleanup_execve_memory(char **argv, char *command, char *pathname)
{
	int	i;

	i = 0;
	if (command)
	{
		free(command);
		command = NULL;
	}
	if (pathname)
	{
		free(pathname);
		pathname = NULL;
	}
	while (argv && argv[i])
	{
		if (argv[i])
			free(argv[i]);
		argv[i] = NULL;
		i++;
	}
	if (argv)
		argv = NULL;
}

static int	handle_execve_error(t_minishell *mini, char **argv, \
			char *command, int error_code)
{
	mini->exit_status = error_code;
	cleanup_execve_memory(argv, command, NULL);
	return (-1);
}

static int	handle_path(t_minishell *mini, char **argv, char **pathname)
{
	int	error_code;

	if (ft_strchr(mini->command, '/') || mini->command[0] == '.')
	{
		error_code = execpath_error(mini->command);
		if (error_code != 0)
			return (handle_execve_error(mini, argv, mini->command, error_code));
		*pathname = ft_strdup(mini->command);
	}
	else
	{
		error_code = handle_search_path(mini, mini->commands->tokens, pathname);
		if (!*pathname)
			return (handle_execve_error(mini, argv, mini->command, 127));
	}
	return (0);
}

int	exec_child(t_minishell *mini, char **argv, char *pathname)
{
	close(mini->saved_stdin);
	mini->saved_stdin = -1;
	close(mini->saved_stdout);
	mini->saved_stdout = -1;
	restore_default_signals();
	if (mini->commands->fd[0] != -1)
		close(mini->commands->fd[0]);
	if (mini->commands->fd[1] != -1)
		close(mini->commands->fd[1]);
	if (execve(pathname, argv, mini->envp) == -1)
	{
		handle_execve_error(mini, argv, mini->command, 126);
		exit(mini->exit_status);
		return (-1);
	}
	return (mini->exit_status);
}

int	execute_execve(t_minishell *mini)
{
	char	**argv;
	char	*pathname;
	int		i;
	int		status;
	pid_t	pid;

	pathname = NULL;
	status = 0;
	get_command(mini);
	i = count_node(mini);
	argv = get_argv(mini, i, mini->commands->tokens);
	if (!argv)
		return (handle_execve_error(mini, NULL, mini->command, 1));
	if (handle_path(mini, argv, &pathname) != 0)
		return (mini->exit_status);
	if (mini->has_pipe > 0)
		restore_default_signals();
	pid = create_pid();
	if (pid == 0)
		if (exec_child(mini, argv, pathname) == -1)
			return (mini->exit_status);
	waitpid(pid, &status, 0);
	feel_signals(mini, status);
	cleanup_execve_memory(argv, mini->command, pathname);
	return (mini->exit_status);
}
