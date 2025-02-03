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

/* int	custom_fork(t_minishell *mini)
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
} */

//TODO apagar: funcao de testes para ver se cmds estao a ficar bem guardados
void print_commands(t_minishell *mini)
{
    t_cmd *cmd;
    t_node *token;
    
    cmd = mini->commands;
    while (cmd)
    {
        token = cmd->tokens;
       // printf("Command: ");
        while (token)
        {
            //printf("%s ", token->token);
            token = token->next;
        }
        //printf("\n");
        cmd = cmd->next;
    }
}

void run_cmd(t_minishell *mini, int *prev_fd)
{
    if (*prev_fd != -1)
        redir_fds(*prev_fd, STDIN_FILENO);
    if (mini->commands->next)
        redir_fds(mini->commands->fd[1], STDOUT_FILENO);
    if (mini->commands->fd[0] != -1)
        close(mini->commands->fd[0]);

    // Execute command
    execute_execve(mini);
    
    // If execve fails, exit child process
    perror("execve failed");
    exit(1);
}




/* void	run_cmd(t_minishell *mini, int *prev_fd)
{
	if (*prev_fd != -1)
		redir_fds(*prev_fd, STDIN_FILENO);
	if (mini->commands->next)
		redir_fds(mini->commands->fd[1], STDOUT_FILENO);
	if (mini->commands->fd[0] != -1)
		close(mini->commands->fd[0]);
	first_token(mini);
	//free_list(mini);
	//free_commands(mini);
} */

void	exec_commands(t_minishell *mini, int *prev_fd)
{
    pid_t	pid;
	int		status;

    pid = create_pid();
    if (pid == 0) // Child process
    {
        if (*prev_fd != -1) // Redirect stdin
        {
            //printf("Child process: Redirecting prev_fd %d -> stdin\n", *prev_fd);
            redir_fds(*prev_fd, STDIN_FILENO);
        }
        if (mini->commands->next) // Redirect stdout if there's another command
        {
            //printf("Child process: Redirecting cmd->fd[1] %d -> stdout\n", mini->commands->fd[1]);
            redir_fds(mini->commands->fd[1], STDOUT_FILENO);
        }

        // Close both ends of the pipe in the child
        if (mini->commands->fd[0] != -1)
            close(mini->commands->fd[0]);
        if (mini->commands->fd[1] != -1)
            close(mini->commands->fd[1]);

        first_token(mini); // Execute command (execve or builtin)
        exit(mini->exit_status); // Ensure child exits
    }
	waitpid(pid, &status, 0);
    // Parent process
    if (*prev_fd != -1)
    {
        //printf("Parent closing prev_fd %d (was stdin for previous cmd)\n", *prev_fd);
        close(*prev_fd);
    }
    if (mini->commands->next) // Close write end in parent
    {
        //printf("Parent closing cmd->fd[1] %d\n", mini->commands->fd[1]);
        close(mini->commands->fd[1]);
    }
    // Keep read end open for next command
	*prev_fd = mini->commands->fd[0];
    //printf("Parent: Saving cmd->fd[0] %d as prev_fd for next command\n", *prev_fd);
    mini->child[mini->i++] = pid;
}




/* void	exec_commands(t_minishell *mini, int *prev_fd)
{
	pid_t	pid;

	pid = create_pid();
	if (pid == 0) // Child Process
	{
		run_cmd(mini, prev_fd);
		exit(1); // This should never be reached
	}
	else if (pid > 0) // Parent Process
	{
		if (*prev_fd != -1)
			close(*prev_fd); // Close previous read end in parent
		if (mini->commands->next)
			close(mini->commands->fd[1]); // Close current write end in parent
		*prev_fd = mini->commands->fd[0]; // Update prev_fd for the next command
		mini->child[mini->i++] = pid;
	}
} */


//EXEC_CHILD
/* void	exec_commands(t_minishell *mini, int *prev_fd)
{
	pid_t	pid;

	pid = create_pid();
	if (pid == 0)
		run_cmd(mini, prev_fd);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (mini->commands->next)
		close(mini->commands->fd[1]);
	*prev_fd = mini->commands->fd[0];
	mini->child[mini->i++] = pid;
} */

void exec_multiple_cmds(t_minishell *mini)
{
	t_cmd	*temp_cmd;
	t_cmd	*old_cmd;
	int		n_cmds;
	int		prev_fd;
	int		temp_fd[1024];
	int		i;

	i = 0;
	create_pipes(mini->commands, temp_fd);
	prev_fd = -1;
	n_cmds = get_ncmds(mini->commands);
	while (mini->commands)
	{
		exec_commands(mini, &prev_fd);
		temp_cmd = mini->commands->next;
		//if (mini->commands->fd[0] != -1) // Close only after execution
			//close(mini->commands->fd[0]);
		// if (mini->commands->fd[1] != -1)
		// 	close(mini->commands->fd[1]);
		free_tokens(mini->commands->tokens);
		old_cmd = mini->commands;
		mini->commands = temp_cmd;
		free(old_cmd);
	}
	while (temp_fd[i])
	{
		close(temp_fd[i++]);
	}
	
	//close(prev_fd);
	wait_childs(mini, n_cmds);
}


/* void exec_multiple_cmds(t_minishell *mini)
{
	//pid_t	pid;
	t_cmd	*temp_cmd;
	t_cmd	*old_cmd;
	int		n_cmds;
	int		prev_fd;

	create_pipes(mini->commands);
	prev_fd = -1;
	n_cmds = get_ncmds(mini->commands);
	while (mini->commands)
	{
		//pid = create_pid()
		exec_commands(mini, &prev_fd);
		temp_cmd = mini->commands->next;
		close(mini->commands->fd[0]);
		close(mini->commands->fd[1]);
		free_tokens(mini->commands->tokens);
		mini->commands->next = NULL;
		old_cmd = mini->commands;
		mini->commands = temp_cmd;
		free(old_cmd);
	}
	wait_childs(mini, n_cmds);
} */

void	exec_cmds(t_minishell *mini)
{
/* 	t_node	*tokenlst;

	tokenlst = mini->tokenlst; */
	split_commands(mini);
	print_commands(mini); //TODO apagar
	
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
		*ret = execute_execve(mini);
		//*ret = custom_fork(mini);
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
	//printf("exit status: %d\n", mini->exit_status);//TODO apagar - teste
	return (ret);
}
