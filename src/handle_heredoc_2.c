/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:52:58 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/10 10:13:13 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	support_fill_fr_heredoc(t_heredoc *tmp_hd, t_minishell *mini)
{
	if (close(tmp_hd->fd_heredoc) == -1)
		perror("Failed to close heredoc file");
	close(mini->saved_stdout);
	close(mini->saved_stdin);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	open_heredoc(t_heredoc *tmp_hd)
{
	tmp_hd->fd_heredoc = open(tmp_hd->fd_heredoc_path, O_CREAT | O_RDWR | \
			O_TRUNC, 0644);
	if (tmp_hd->fd_heredoc == -1)
		return (-1);
	return (0);
}

int	fill_fd_heredoc(t_heredoc *tmp_hd, t_minishell *mini)
{
	char	*line;

	open_heredoc(tmp_hd);
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
		if (write(tmp_hd->fd_heredoc, line, ft_strlen(line)) == -1 || \
				write(tmp_hd->fd_heredoc, "\n", 1) == -1)
			perror("Error writing heredoc line");
		free (line);
	}
	support_fill_fr_heredoc(tmp_hd, mini);
	return (0);
}
