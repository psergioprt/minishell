/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:08:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/06 18:28:49 by jcavadas         ###   ########.fr       */
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
		num = ft_itoa(tmp_hd->index);
		tmp_hd->fd_heredoc_path = ft_strjoin("/tmp/tmp_heredoc", num);
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
	
	//TODO: FAZER ISTO
	t_node *tokenlst = mini->tokenlst;

	printf("UWU\n");

	while (tokenlst->type != HEREDOC && tokenlst)
	{
		printf("owo\n");
		printf("token: %s\n", tokenlst->token);
		printf("token->type: %d\n", tokenlst->type);
		if (tokenlst->token && tokenlst->type == HEREDOC)
			printf("tou ken: %s\n", tokenlst->token);
		tokenlst = tokenlst->next;
	}
	


}