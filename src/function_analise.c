/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_analise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:59 by marvin            #+#    #+#             */
/*   Updated: 2025/01/22 20:04:04 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	custom_fork(t_minishell *mini)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		printf("Fork error");
		exit(EXIT_FAILURE);
/* 		perror("fork");*/
	}
	else if (pid == 0) {
		// Child process
		printf("Executing command in child process (PID: %d)\n", getpid()); //TODO apagar
		restore_default_signals();
		// Execute the command using execve
		if (execute_execve(mini) == -1) {
			printf("execve error");
			exit(EXIT_FAILURE); // Exit the child process if execve fails
		}
	} else {
		// Parent process
		printf("Parent process waiting for child (PID: %d)\n", pid);

		// Wait for the child process to finish
		if (waitpid(pid, &status, 0) == -1) {
			printf("waitpid error");
			exit(EXIT_FAILURE);
		}

		 // Check child's exit status
		if (WIFEXITED(status))
		{
			mini->exit_status = WEXITSTATUS(status);
			printf("mini->exit_status: %d\n", mini->exit_status);
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			mini->exit_status = 128 + WTERMSIG(status);
			printf("Child process terminated by signal: %d\n", WTERMSIG(status)); 
		}
	}
	return (1);
}

int	first_token(t_minishell *mini)
{
	int		ret;
	size_t	len;

	ret = 0;
	if (mini->tokenlst && mini->tokenlst->token)//UPDATED BY PAULO. $x caused SEGFAULT
	{
		len = ft_strlen(mini->tokenlst->token);
		if (!ft_strncmp(mini->tokenlst->token, "echo", len))
			ret = custom_echo(mini);
			// printf("Fazer o echo\n");
		else if (!ft_strncmp(mini->tokenlst->token, "cd", len))
			ret = custom_cd(mini);
			//printf("Fazer o cd\n");
		else if (!ft_strncmp(mini->tokenlst->token, "pwd", len))
			ret = custom_pwd(mini);
			//printf("Fazer o pwd\n");
		else if (!ft_strncmp(mini->tokenlst->token, "export", len))
			ret = custom_export(mini);
			//printf("Fazer o export\n");
		else if (!ft_strncmp(mini->tokenlst->token, "unset", len))
			ret = custom_unset(mini);
			//printf("Fazer o unset\n");
		else if (!ft_strncmp(mini->tokenlst->token, "env", len))
			ret = custom_env(mini);	
			//printf("Fazer o env\n");
		else if (!ft_strncmp(mini->tokenlst->token, "exit", len))
			printf("Fazer o exit\n");
		else
			ret = custom_fork(mini);
	}
	if (ret <= 0 && mini->tokenlst && mini->tokenlst->token)
		printf("Error, command not found!\n");
	return (ret);
}
