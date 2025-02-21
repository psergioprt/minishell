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

void	exec_commands(t_minishell *mini, int *prev_fd)
{
	pid_t	pid;

	if (has_heredoc(mini))
		heredoc(mini, prev_fd);
	pid = create_pid();
	if (pid == 0)
		handle_child_process(mini, prev_fd);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (mini->commands->next)
		close(mini->commands->fd[1]);
	*prev_fd = mini->commands->fd[0];
	mini->child[mini->i++] = pid;
}

void	exec_multiple_cmds(t_minishell *mini)
{
	t_cmd	*temp_cmd;
	t_cmd	*old_cmd;
	int		n_cmds;
	int		prev_fd;

	prev_fd = -1;
	n_cmds = get_ncmds(mini->commands);
	while (mini->commands)
	{
		create_pipes(mini->commands);
		exec_commands(mini, &prev_fd);
		temp_cmd = mini->commands->next;
		free_tokens(mini->commands->tokens);
		old_cmd = mini->commands;
		mini->commands = temp_cmd;
		free(old_cmd);
		init_sigaction(mini->interactive);
	}
	wait_childs(mini, n_cmds);
	mini->i = 0;
	if (prev_fd != -1)
		close(prev_fd);
}

void	exec_cmds(t_minishell *mini)
{
	mini->prev_node = NULL;
	split_commands(mini);
	if (check_redirect_errors(mini))
	{
		mini->exit_status = 2;
		return ;
	}
	if (mini->commands && !mini->commands->next)
	{
		if (has_heredoc(mini))
			heredoc(mini, NULL);
		if (handle_redirections(mini) == -1)
			return ;
		skip_redirection_plus_target(mini);
		first_token(mini);
	}
	else
		exec_multiple_cmds(mini);
}

void	execute(t_minishell *mini, t_cmd *cmdlst)
{
	size_t	len;

	if (!mini->tokenlst || !mini->tokenlst->token)
		return ;
	len = ft_strlen(cmdlst->tokens->token);
	if (!ft_strncmp(cmdlst->tokens->token, "echo", len))
		mini->exit_status = custom_echo(mini);
	else if (!ft_strncmp(cmdlst->tokens->token, "cd", len))
		mini->exit_status = custom_cd(mini);
	else if (!ft_strncmp(cmdlst->tokens->token, "pwd", len))
		mini->exit_status = custom_pwd(mini);
	else if (!ft_strncmp(cmdlst->tokens->token, "export", len))
		mini->exit_status = custom_export(mini);
	else if (!ft_strncmp(cmdlst->tokens->token, "unset", len))
		mini->exit_status = custom_unset(mini);
	else if (!ft_strncmp(cmdlst->tokens->token, "env", len))
		mini->exit_status = custom_env(mini);
	else if (!ft_strncmp(cmdlst->tokens->token, "exit", len))
		mini->exit_status = custom_exit(mini);
	else
		mini->exit_status = execute_execve(mini);
}

int	first_token(t_minishell *mini)
{
	t_cmd	*cmdlst;

	if (mini->commands && mini->commands->tokens \
		&& mini->commands->tokens->token)
	{
		cmdlst = mini->commands;
		if (!cmdlst || !cmdlst->tokens || !cmdlst->tokens->token)
			return (1);
		if (cmdlst->tokens->token[0] == '\0')
		{
			write(2, "'': command not found\n", 23);
			mini->exit_status = 127;
			return (127);
		}
		execute(mini, cmdlst);
	}
	return (0);
}
