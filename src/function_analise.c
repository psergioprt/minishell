/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_analise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:59 by marvin            #+#    #+#             */
/*   Updated: 2025/01/30 08:18:37 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	custom_fork(t_minishell *mini)
{
	pid_t	pid;
	int		status;

	pid = fork();
	printf("fork returned: %d\n", pid);
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
		printf("INSIDE PID == 0\n");
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
	return (0);
}
//TODO: mudar logica para dar os error codes
//
//
int	first_token(t_minishell *mini)
{
	int		ret;
	size_t	len;
	int 		saved_stdout;
	int		saved_stdin;

	ret = 0;
	if (mini->tokenlst && mini->tokenlst->token)
	{
		len = ft_strlen(mini->tokenlst->token);
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		if (handle_redirections(mini) == -1)
		{
			perror("Redirection error");
			close(saved_stdout);
			close(saved_stdin);
			return (-1);
		}
		skip_redirection_plus_target(mini);
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
			printf("Fazer o exit\n"); // TODO: Implement exit
		else
			ret = custom_fork(mini);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
	}
	// if (ret <= 0)
	//	printf("Error, command not found!\n");
	//mini->exit_status = ret;
	printf("exit status: %d\n", mini->exit_status);//TODO apagar - teste
	return (ret);
}
