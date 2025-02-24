/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:10:16 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/24 15:31:33 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_ctrl_c_hd(t_minishell *mini)
{
	close(mini->saved_stdout);
	close(mini->saved_stdout);
	close(mini->commands->fd[1]);
	close(mini->commands->fd[0]);
	close(mini->heredoc->fd_heredoc);
}

void	handle_heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		g_exit_code = SIGINT;
		close(STDIN_FILENO);
	}
}

void	set_signals_to_here_doc(void)
{
	signal(SIGINT, handle_heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (joined);
}

int	check_malloc(void *ptr)
{
	if (!ptr)
	{
		perror("malloc failed");
		return (1);
	}
	return (0);
}
