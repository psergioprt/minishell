/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:08:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/24 15:37:30 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	identify_redirection_type(char *token)
{
	if (!ft_strcmp(token, ">"))
		return (OUTPUT);
	if (!ft_strcmp(token, ">>"))
		return (APPEND_OUTPUT);
	if (!ft_strcmp(token, "<"))
		return (INPUT);
	if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	return (-1);
}

void	redir_error_close(t_minishell *mini)
{
	if (mini->commands->fd[0] != -1)
		close(mini->commands->fd[0]);
	if (mini->commands->fd[1] != -1)
		close(mini->commands->fd[1]);
	if (mini->heredoc->fd_heredoc != -1)
		close(mini->heredoc->fd_heredoc);
	close(mini->saved_stdin);
	close(mini->saved_stdout);
}

void	close_fds(t_minishell *mini, t_heredoc *tmp_hd, char *line)
{
	free(line);
	close(tmp_hd->fd_heredoc);
	close(mini->heredoc->fd_heredoc);
	close(mini->saved_stdin);
	close(mini->saved_stdout);
	if (mini->commands->fd[0] != -1)
		close(mini->commands->fd[0]);
	if (mini->commands->fd[1] != -1)
		close(mini->commands->fd[1]);
}

void	support_heredoc(t_heredoc *tmp_hd, t_minishell *mini, int *prev_fd)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		g_exit_code = 0;
		if (prev_fd != NULL && *prev_fd != -1)
			close(*prev_fd);
		handle_heredoc_child(tmp_hd, mini);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(mini->saved_stdout);
		close(mini->saved_stdout);
		close(mini->commands->fd[1]);
		close(mini->commands->fd[0]);
		close(mini->heredoc->fd_heredoc);
		handle_ctrl_c_hd(mini);
		return ;
	}
}

void	heredoc(t_minishell *mini, int *prev_fd)
{
	t_heredoc	*tmp_hd;

	save_heredoc_info(mini);
	if (mini->heredoc && mini->heredoc->eof == NULL)
		tmp_hd = mini->heredoc->next;
	else
		tmp_hd = mini->heredoc;
	while (tmp_hd)
	{
		tmp_hd->fd_heredoc_path = ft_strjoin("/tmp/tmp_heredoc", \
									ft_itoa(tmp_hd->index));
		if (!tmp_hd->done)
			support_heredoc(tmp_hd, mini, prev_fd);
		tmp_hd->done = true;
		tmp_hd = tmp_hd->next;
	}
	change_targets(mini);
	include_hd_path(mini);
}
