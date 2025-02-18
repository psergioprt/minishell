/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:52:58 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/18 20:56:22 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_child_process(t_minishell *mini, int *prev_fd)
{
	if (*prev_fd != -1)
		redir_fds(*prev_fd, STDIN_FILENO);
	if (mini->commands->next)
		redir_fds(mini->commands->fd[1], STDOUT_FILENO);
 	if (mini->heredoc->fd_heredoc)
		close(mini->heredoc->fd_heredoc);
/* 	if (has_heredoc(mini))
		heredoc(mini); */
 	if (handle_redirections(mini) == -1)//Comentar isto funciona ls | grep a < Makefile mas estraga cat Makefile | grep NAME > file
	{
		if (mini->commands->fd[0] != -1)
			close(mini->commands->fd[0]);
		if (mini->commands->fd[1] != -1)
			close(mini->commands->fd[1]);
		if (mini->heredoc->fd_heredoc != -1)
			close(mini->heredoc->fd_heredoc);
		close(mini->saved_stdin);
		close(mini->saved_stdout);
		exit(mini->exit_status);
	}
	skip_redirection_plus_target(mini);
	
	first_token(mini);
	
	if (mini->commands->fd[0] != -1)
		close(mini->commands->fd[0]);
	if (mini->commands->fd[1] != -1)
		close(mini->commands->fd[1]);

/*  	if (handle_redirections(mini) == -1) 
		return ;
	skip_redirection_plus_target(mini); */ //Comentar isto funciona cat Makefile | grep NAME > file mas estraga ls | grep a < Makefile
/* 	remove_heredoc_token(mini);
	first_token(mini); */
	close(mini->saved_stdin);
	close(mini->saved_stdout);
	exit(mini->exit_status);
}

void	support_fill_fr_heredoc(t_heredoc *tmp_hd, t_minishell *mini)
{
	if (close(tmp_hd->fd_heredoc) == -1)
		perror("Failed to close heredoc file");
	close(mini->heredoc->fd_heredoc);
	close(mini->saved_stdout);
	close(mini->saved_stdin);
	if (mini->commands->fd[0] != -1)
		close(mini->commands->fd[0]);
	if (mini->commands->fd[1] != -1)
		close(mini->commands->fd[1]);
	/* 	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO); */
}

int	open_heredoc(t_heredoc *tmp_hd)
{
	tmp_hd->fd_heredoc = open(tmp_hd->fd_heredoc_path, O_CREAT | O_RDWR | \
			O_TRUNC, 0644);
	if (tmp_hd->fd_heredoc == -1)
		return (-1);
	return (0);
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

int	fill_fd_heredoc(t_heredoc *tmp_hd, t_minishell *mini)
{
	char	*line;

	//set_signals_to_here_doc();
	open_heredoc(tmp_hd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close_fds(mini, tmp_hd, line);
			return (0);
		}
		if (ft_strcmp(line, tmp_hd->eof) == 0)
		{
			free(line);
			break ;
		}
		if (!tmp_hd->eof_quote)
			check_hd_expand(&line, mini);
		if (write(tmp_hd->fd_heredoc, line, ft_strlen(line)) == -1 || \
				write(tmp_hd->fd_heredoc, "\n", 1) == -1)
			perror("Error writing heredoc line");
		free (line);
	}
	restore_default_signals();
	support_fill_fr_heredoc(tmp_hd, mini);
	return (0);
}
