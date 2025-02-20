/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:08:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/20 23:18:32 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	support_heredoc(t_heredoc *tmp_hd, t_minishell *mini, int *prev_fd)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
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
		if (!tmp_hd->done)
			support_heredoc(tmp_hd, mini, prev_fd);
		tmp_hd->done = true;
		tmp_hd = tmp_hd->next;
	}
	include_hd_path(mini);
}
