/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:31:02 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/27 14:31:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int handle_direct_path(t_minishell *mini, char **argv)
{
	int error_code = execpath_error(mini->command);
	if (error_code != 0)
	{
		mini->exit_status = error_code;
		free(mini->command);
		int j = 0;
		while (argv[j])
			free(argv[j++]);
		free(argv);
		return (-1);
	}
	return (0);
}

void	feel_signals(t_minishell *mini, int status)
{
	if (WIFEXITED(status))
	{
		mini->exit_status = WEXITSTATUS(status);
		printf("mini->exit_status: %d\n", mini->exit_status);//TODO apagar testes
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		mini->exit_status = 128 + WTERMSIG(status);
		printf("Child process terminated by signal: %d\n", WTERMSIG(status));//TODO apagar testes
	}
}
