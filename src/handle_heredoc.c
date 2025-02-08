/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:08:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/08 14:58:14 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	save_heredoc_info(t_minishell *mini)
{
	t_node	*tmp = mini->tokenlst;
	t_heredoc	*tmp_hd = NULL;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->next)
		{
			if (!mini->heredoc)
			{
				mini->heredoc = malloc(sizeof(t_heredoc));
				if (check_malloc(mini->heredoc))
					return ;
				mini->heredoc->index = 1;
				mini->heredoc->eof = ft_strdup(tmp->next->token);
				mini->heredoc->eof_quote = false;
				mini->heredoc->fd_heredoc_path = NULL;
				mini->heredoc->count_hd = 0;
				mini->heredoc->next = NULL;
				if (!mini->heredoc->eof)
					fprintf(stderr, "Error: HEREDOC delimiter is NULL\n");
			}
			else
			{
				if (!mini->heredoc->eof)
				{
					mini->heredoc->eof = ft_strdup(tmp->next->token);
					if (!mini->heredoc->eof)
						fprintf(stderr, "Error: HEREDOC delimiter is NULL\n");
				}
				else
				{
					tmp_hd = mini->heredoc;
					while (tmp_hd->next)
						tmp_hd = tmp_hd->next;
					tmp_hd->next = malloc(sizeof(t_heredoc));
					if (check_malloc(tmp_hd->next))
						return ;
					tmp_hd = tmp_hd->next;
					tmp_hd->index = mini->heredoc->index + 1;
					tmp_hd->eof = ft_strdup(tmp->next->token);
					tmp_hd->eof_quote = false;
					tmp_hd->fd_heredoc_path = NULL;
					tmp_hd->count_hd = mini->heredoc->count_hd;
					tmp_hd->next = NULL;
					if (!tmp_hd->eof)
						fprintf(stderr, "Error: HEREDOC delimiter is NULL\n");
				}
			}
		}
		tmp = tmp->next;
	}
}

int	fill_fd_heredoc(t_heredoc *tmp_hd, t_minishell *mini)
{
	char	*line;

	tmp_hd->fd_heredoc = open(tmp_hd->fd_heredoc_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_hd->fd_heredoc == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			return (0);
		}
		if (ft_strcmp(line, tmp_hd->eof) == 0)
		{
			free(line);
			break ;
		}
		if (!tmp_hd->eof_quote)
			check_hd_expand(&line, mini);
		if (write(tmp_hd->fd_heredoc, line, ft_strlen(line)) == -1 || write(tmp_hd->fd_heredoc, "\n", 1) == -1)
            		perror("Error writing heredoc line");
		free (line);
	}
	if (close(tmp_hd->fd_heredoc) == -1)
		perror("Failed to close heredoc file");
	return (0);
}



void	remove_heredoc_token(t_minishell *mini)
{
	t_node	*prev_token = NULL;
	t_node	*current_token = mini->tokenlst;
	t_node	*prev_cmd = NULL;
	t_node	*current_cmd = mini->commands->tokens;

	// Remove from tokenlst
	while (current_token)
	{
		if (current_token->type == HEREDOC) // Found "<<"
		{
			if (prev_token)
				prev_token->next = current_token->next;
			else
				mini->tokenlst = current_token->next;
			
			free(current_token->token);
			free(current_token);
			current_token = (prev_token) ? prev_token->next : mini->tokenlst;
			continue;
		}
		prev_token = current_token;
		current_token = current_token->next;
	}

	// Remove from commands->tokens
	while (current_cmd)
	{
		if (current_cmd->type == HEREDOC) // Found "<<"
		{
			if (prev_cmd)
				prev_cmd->next = current_cmd->next;
			else
				mini->commands->tokens = current_cmd->next;
			
			free(current_cmd->token);
			free(current_cmd);
			current_cmd = (prev_cmd) ? prev_cmd->next : mini->commands->tokens;
			continue;
		}
		prev_cmd = current_cmd;
		current_cmd = current_cmd->next;
	}
}

void	heredoc(t_minishell *mini)
{
	t_heredoc	*tmp_hd;
	char		*num;
	int			status;
	pid_t		pid;
	
	save_heredoc_info(mini);
	if (mini->heredoc && mini->heredoc->eof == NULL)
		tmp_hd = mini->heredoc->next;
	else
		tmp_hd = mini->heredoc;
	while (tmp_hd)
	{
		char	cwd[1024];
		char	*directory;
		directory = getcwd(cwd, sizeof(cwd));
		tmp_hd->fd_heredoc_path = ft_strjoin(directory, "/");
		tmp_hd->fd_heredoc_path = ft_strjoin(tmp_hd->fd_heredoc_path, mini->heredoc->eof);
		num = ft_itoa(tmp_hd->index);
		//tmp_hd->fd_heredoc_path = ft_strjoin("/tmp/tmp_heredoc", num);
		free(num);
		pid = fork();
		if (pid == 0)
			handle_heredoc_child(tmp_hd, mini);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			handle_ctrl_c_hd(mini);
			return ;
		}
		tmp_hd = tmp_hd->next;
	}
	include_hd_path(mini);
	remove_heredoc_token(mini);
}
