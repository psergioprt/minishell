/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:08:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/10 09:55:11 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	support_heredoc_token_tokens(t_minishell *mini)
{
	t_node	*prev_token;
	t_node	*current_token;

	prev_token = NULL;
	current_token = mini->tokenlst;
	while (current_token)
	{
		if (current_token->type == HEREDOC)
		{
			if (prev_token)
				prev_token->next = current_token->next;
			else
				mini->tokenlst = current_token->next;
			free(current_token->token);
			free(current_token);
			if (prev_token)
				current_token = prev_token->next;
			else
				current_token = mini->tokenlst;
			continue ;
		}
		prev_token = current_token;
		current_token = current_token->next;
	}
}

void	support_heredoc_token_commands(t_minishell *mini)
{
	t_node	*prev_cmd;
	t_node	*current_cmd;

	prev_cmd = NULL;
	current_cmd = mini->commands->tokens;
	while (current_cmd)
	{
		if (current_cmd->type == HEREDOC)
		{
			if (prev_cmd)
				prev_cmd->next = current_cmd->next;
			else
				mini->commands->tokens = current_cmd->next;
			free(current_cmd->token);
			free(current_cmd);
			if (prev_cmd)
				current_cmd = prev_cmd->next;
			else
				current_cmd = mini->commands->tokens;
			continue ;
		}
		prev_cmd = current_cmd;
		current_cmd = current_cmd->next;
	}
}

void	remove_heredoc_token(t_minishell *mini)
{
	support_heredoc_token_tokens(mini);
	support_heredoc_token_commands(mini);
}

void	support_heredoc(t_heredoc *tmp_hd, t_minishell *mini)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_heredoc_child(tmp_hd, mini);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		handle_ctrl_c_hd(mini);
		return ;
	}
}

void	heredoc(t_minishell *mini)
{
	t_heredoc	*tmp_hd;
	char		*num;
	char		cwd[1024];
	char		*directory;

	save_heredoc_info(mini);
	if (mini->heredoc && mini->heredoc->eof == NULL)
		tmp_hd = mini->heredoc->next;
	else
		tmp_hd = mini->heredoc;
	while (tmp_hd)
	{
		directory = getcwd(cwd, sizeof(cwd));
		tmp_hd->fd_heredoc_path = ft_strjoin(directory, "/");
		tmp_hd->fd_heredoc_path = ft_strjoin(tmp_hd->fd_heredoc_path, \
				mini->heredoc->eof);
		num = ft_itoa(tmp_hd->index);
		free(num);
		support_heredoc(tmp_hd, mini);
		tmp_hd = tmp_hd->next;
	}
	include_hd_path(mini);
	remove_heredoc_token(mini);
}
