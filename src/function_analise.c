/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_analise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:59 by marvin            #+#    #+#             */
/*   Updated: 2024/11/20 16:33:59 by marvin           ###   ########.fr       */
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

		// Execute the command using execve
		if (execute_execve(mini) == -1) {
			printf("execve error\n");
			exit(127); // Exit the child process if execve fails
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
			mini->exit_status = 128 + WTERMSIG(status);
			printf("Child process terminated by signal: %d\n", WTERMSIG(status));
		}
	}
	return (0);
}
//TODO: mudar logica para dar os error codes
int	first_token(t_minishell *mini)
{
	int		ret;
	size_t	len;

	ret = 0;
	len = ft_strlen(mini->tokenlst->token);
	if (!ft_strncmp(mini->tokenlst->token, "echo", len))
		mini->exit_status = custom_echo(mini);//correct exit codes
	else if (!ft_strncmp(mini->tokenlst->token, "cd", len))
		mini->exit_status = custom_cd(mini);//correct exit codes
	else if (!ft_strncmp(mini->tokenlst->token, "pwd", len))
		mini->exit_status = custom_pwd(mini);//correct exit codes
	else if (!ft_strncmp(mini->tokenlst->token, "export", len))
		mini->exit_status = custom_export(mini);//correct exit codes
	else if (!ft_strncmp(mini->tokenlst->token, "unset", len))
		mini->exit_status = custom_unset(mini);//correct exit codes
	else if (!ft_strncmp(mini->tokenlst->token, "env", len))
		mini->exit_status = custom_env(mini);//correct exit codes
	else if (!ft_strncmp(mini->tokenlst->token, "exit", len))
		printf("Fazer o exit\n"); //TODO
	else
		ret = custom_fork(mini); //TODO corrigir/verificar exit codes
	/* if (ret <= 0)
		printf("Error, command not found!\n"); */
	//mini->exit_status = ret;
	printf("exit status: %d\n", mini->exit_status);
	return (ret);
}
