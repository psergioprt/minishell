/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:35:07 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/07 11:57:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_search_path(t_minishell *mini, t_node *node, char **pathname)
{
	*pathname = find_path(mini);
	if (!*pathname)
	{
		printf("%s: command not found\n", node->token);
		mini->exit_status = 127;
		return (-1);
	}
	return (0);
}

static void	cleanup_execve_memory(char **argv, char *command, char *pathname)
{
	int	i;

	i = 0;
	free(command);
	free(pathname);
	while (argv && argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
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

int	execute_execve(t_minishell *mini)
{
	char	**argv;
	char	*pathname;
	int		i;
	int		status;
	pid_t	pid;

	pathname = NULL;
	get_command(mini);
	i = count_node(mini);
	argv = get_argv(mini, i, mini->commands->tokens);
	if (!argv)
		return (handle_execve_error(mini, NULL, mini->command, 1));
	if (handle_path(mini, argv, &pathname) != 0)
		return (-1);
	//ignore_signals(); //TODO CREATED FOR THE ISSUE #10 SIGNAL ERRORS
	pid = create_pid();
	if (pid == 0)
	{
		close(mini->saved_stdin);
		close(mini->saved_stdout);
		restore_default_signals();
		if (execve(pathname, argv, mini->envp) == -1)
			return (handle_execve_error(mini, argv, mini->command, 126));
	}
	waitpid(pid, &status, 0);
	feel_signals(mini, status);
	cleanup_execve_memory(argv, mini->command, pathname);
	//restore_default_signals();//TODO Corrige cntrl C a nao funcionar depois de cat sem arg, mas cntrl c fecha programa 
	return (mini->exit_status);
}
