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

//cat test.txt | grep "apple" | wc -l
//2 pipes, 3 comandos

void create_pipes(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->next)
	{
		if (pipe(cmd->fd) == -1)
		{
			perror("Error creating pipes");
			exit(1);
		}
		//printf("Pipe created: fd[0]=%d, fd[1]=%d\n", cmd->fd[0], cmd->fd[1]);
	}
	//cmd = cmd->next;
	
}


/* void	create_pipes(t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->next && pipe(cmd->fd) == -1)
		{
			printf("Error creating pipes\n");
			return ;
		}
		cmd = cmd->next;
	}
	return ;
} */

void redir_fds(int redir, int local)
{
	if (redir < 0 || local < 0)
	{
		perror("Invalid file descriptor");
		return;
	}
	//printf("Redirecting %d -> %d\n", redir, local);
	
	if (fcntl(redir, F_GETFD) == -1)
	{
		perror("FD check failed before dup2");
		return;
	}

	if (dup2(redir, local) < 0)
	{
		perror("dup2 failed");
		printf("Failed to redirect %d -> %d\n", redir, local);
		close(redir);
		return;
	}
	close(redir);
}


/* void redir_fds(int redir, int local)
{
	if (redir < 0 || local < 0)
	{
		perror("Invalid file descriptor");
		return;
	}
	printf("Redirecting %d -> %d\n", redir, local);
	
	if (dup2(redir, local) < 0)
	{
		perror("dup2 failed");
		printf("Failed to redirect %d -> %d\n", redir, local);
		close(redir);
		return;
	}
	close(redir);
} */


void	wait_childs(t_minishell *mini, int n_cmds)
{
	int     i;
	pid_t   pid;

	i = 0;
	while (i < n_cmds)
	{
		pid = waitpid(mini->child[i], &mini->exit_status, 0);
		if (pid == -1)
			perror("waitpid failed");
		else
		{
			if (WIFEXITED(mini->exit_status))
				mini->exit_status = WEXITSTATUS(mini->exit_status);
			else if (WIFSIGNALED(mini->exit_status))
				mini->exit_status = 128 + WTERMSIG(mini->exit_status);
		}
		i++;
	}
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
		printf("Fork error");
		exit(EXIT_FAILURE);	
	}
	return (child);
}

/* int	checking_pipes(t_minishell *mini)
{
	t_node	nodelst;

	nodelst = mini->tokenlst;
	//Fazer ciclo de enquanto tiver pipes
	//O primeiro manda o output
	//Os do meio redirecionam o input do anterior e o output do proximo
	//O ultimo redireciona o input do anterior
}
 */