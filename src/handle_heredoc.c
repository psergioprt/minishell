/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:08:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/10 21:04:23 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_heredoc_token(t_minishell *mini, t_node **current_token, \
		t_node **prev_token, bool *keep_next)
{
	t_node	*heredoc_token;
	t_node	*delim_token;

	heredoc_token = *current_token;
	*current_token = (*current_token)->next;
	if (!*current_token)
		return ;
	if (*keep_next)
		*keep_next = false;
	else
	{
		delim_token = *current_token;
		*current_token = (*current_token)->next;
		free(delim_token->token);
		free(delim_token);
	}
	if (*prev_token)
		(*prev_token)->next = *current_token;
	else
		mini->tokenlst = *current_token;
	free(heredoc_token->token);
	free(heredoc_token);
}

void	support_heredoc_token_tokens(t_minishell *mini)
{
	t_node	*prev_token;
	t_node	*current_token;
	bool	keep_next;

	prev_token = NULL;
	current_token = mini->tokenlst;
	keep_next = true;
	while (current_token)
	{
		if (current_token->type == PIPE)
			break ;
		if (current_token->type == HEREDOC)
			process_heredoc_token(mini, &current_token, &prev_token, \
					&keep_next);
		else
		{
			prev_token = current_token;
			current_token = current_token->next;
		}
	}
}

void	process_heredoc_command(t_minishell *mini, t_node **current_cmd, \
		t_node **prev_cmd, bool *keep_next)
{
	t_node	*heredoc_cmd;
	t_node	*delim_cmd;

	heredoc_cmd = *current_cmd;
	*current_cmd = (*current_cmd)->next;
	if (!*current_cmd)
		return ;
	if (*keep_next)
		*keep_next = false;
	else
	{
		delim_cmd = *current_cmd;
		*current_cmd = (*current_cmd)->next;
		free(delim_cmd->token);
		free(delim_cmd);
	}
	if (*prev_cmd)
		(*prev_cmd)->next = *current_cmd;
	else
		mini->commands->tokens = *current_cmd;
	free(heredoc_cmd->token);
	free(heredoc_cmd);
}

void	support_heredoc_token_commands(t_minishell *mini)
{
	t_node	*prev_cmd;
	t_node	*current_cmd;
	bool	keep_next;

	prev_cmd = NULL;
	current_cmd = mini->commands->tokens;
	keep_next = true;
	while (current_cmd)
	{
		if (current_cmd->type == PIPE)
			break ;
		if (current_cmd->type == HEREDOC)
			process_heredoc_command(mini, &current_cmd, &prev_cmd, &keep_next);
		else
		{
			prev_cmd = current_cmd;
			current_cmd = current_cmd->next;
		}
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
