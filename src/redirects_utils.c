/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:55:03 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/24 16:39:26 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redir_or_close_saved(t_minishell *mini)
{
	if (mini->saved_stdout != -1)
		redir_fds(mini->saved_stdout, STDOUT_FILENO);
	if (mini->saved_stdin != -1)
		redir_fds(mini->saved_stdin, STDIN_FILENO);
	if (mini->saved_stdout != -1)
		close(mini->saved_stdout);
	if (mini->saved_stdin != -1)
		close(mini->saved_stdin);
}

void	change_targets(t_minishell *mini)
{
	t_cmd		*cmd;
	t_node		*token;
	t_heredoc	*tmp_hd;

	cmd = mini->commands;
	tmp_hd = mini->heredoc;
	token = cmd->tokens;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			token->target = ft_strdup(tmp_hd->fd_heredoc_path);
			if (tmp_hd->next)
				tmp_hd = tmp_hd->next;
		}
		token = token->next;
	}
	cmd = cmd->next;
}

int	check_access(t_minishell *mini, char *filename, t_type type)
{
	if (access(filename, F_OK) == 0 && access(filename, R_OK) < 0 && \
		(type == INPUT || type == HEREDOC))
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		mini->exit_status = 1;
		return (-1);
	}
	if (access(filename, F_OK) == 0 && access(filename, W_OK) < 0 && \
		(type == OUTPUT || type == APPEND_OUTPUT))
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		mini->exit_status = 1;
		return (-1);
	}
	return (0);
}
