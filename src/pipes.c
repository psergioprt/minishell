/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:02 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/16 14:52:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_pipes(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->next)
	{
		if (pipe(cmd->fd) == -1)
		{
			perror("Error creating pipes");
			exit(1);
		}
	}
}

void	redir_fds(int redir, int local)
{
	if (redir < 0 || local < 0)
	{
		perror("Invalid file descriptor");
		return ;
	}
	if (fcntl(redir, F_GETFD) == -1)
	{
		perror("FD check failed before dup2");
		return ;
	}
	if (dup2(redir, local) < 0)
	{
		perror("dup2 failed");
		close(redir);
		return ;
	}
	close(redir);
}

void	wait_childs(t_minishell *mini, int n_cmds)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < n_cmds)
	{
		pid = waitpid(mini->child[i], &mini->exit_status, 0);
		if (pid == -1)
			ft_putstr_fd("waitpid error!\n", 2);
		else
		{
			if (WIFEXITED(mini->exit_status))
				mini->exit_status = WEXITSTATUS(mini->exit_status);
			else if (WIFSIGNALED(mini->exit_status))
				mini->exit_status = 128 + WTERMSIG(mini->exit_status);
		}
		i++;
	}
	if (WIFSIGNALED(mini->exit_status) && \
		WTERMSIG(mini->exit_status) == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
}

int	get_ncmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

pid_t	create_pid(void)
{
	pid_t	child;

	child = fork();
	if (child < 0)
	{
		ft_putstr_fd("Fork error", 2);
		exit(EXIT_FAILURE);
	}
	return (child);
}
