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
 		//perror("fork");
	}
	else if (pid == 0) {
		// Child process
		printf("Executing command in child process (PID: %d)\n", getpid()); //TODO apagar
		restore_default_signals();
		// Execute the command using execve
		if (execute_execve(mini) == -1) {
			printf("execve error\n"); //TODO apagar
			exit(mini->exit_status); // Exit the child process if execve fails
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

//TODO apagar: funcao de testes para ver se cmds estao a ficar bem guardados
void print_commands(t_minishell *mini)
{
    t_cmd *cmd;
    t_node *token;
    
    cmd = mini->commands;
    while (cmd)
    {
        token = cmd->tokens;
        printf("Command: ");
        while (token)
        {
            printf("%s ", token->token);
            token = token->next;
        }
        printf("\n");
        cmd = cmd->next;
    }
}

void exec_multiple_cmds(t_minishell *mini)
{
	create_pipes(mini->commands);
}

void	exec_cmds(t_minishell *mini)
{
/* 	t_node	*tokenlst;

	tokenlst = mini->tokenlst; */
	split_commands(mini);
	print_commands(mini);
	
	
	if(mini->commands && !mini->commands->next)
		first_token(mini);
	else
		exec_multiple_cmds(mini);
	//logica se tem pipe -> exec multiple commands
	//else first token
}

void execute(t_minishell *mini, int *ret, t_cmd *cmdlst)
{
	size_t	len;

	len = ft_strlen(cmdlst->tokens->token);
	if (!ft_strncmp(cmdlst->tokens->token, "echo", len))
		mini->exit_status = custom_echo(mini);//correct exit codes
	else if (!ft_strncmp(cmdlst->tokens->token, "cd", len))
		mini->exit_status = custom_cd(mini);//correct exit codes
	else if (!ft_strncmp(cmdlst->tokens->token, "pwd", len))
		mini->exit_status = custom_pwd(mini);//correct exit codes
	else if (!ft_strncmp(cmdlst->tokens->token, "export", len))
		mini->exit_status = custom_export(mini);//correct exit codes
	else if (!ft_strncmp(cmdlst->tokens->token, "unset", len))
		mini->exit_status = custom_unset(mini);//correct exit codes
	else if (!ft_strncmp(cmdlst->tokens->token, "env", len))
		mini->exit_status = custom_env(mini);//correct exit codes
	else if (!ft_strncmp(cmdlst->tokens->token, "exit", len))
		mini->exit_status = custom_exit(mini);
	else
		*ret = custom_fork(mini);
}

//TODO: mudar logica para dar os error codes
int	first_token(t_minishell *mini)
{
	int		ret;
	t_cmd	*cmdlst;

	ret = 0;
	if (mini->commands && mini->commands->tokens && mini->commands->tokens->token)
	{
		cmdlst = mini->commands;
		execute(mini, &ret, cmdlst);
	}
	printf("exit status: %d\n", mini->exit_status);//TODO apagar - teste
	return (ret);
}
