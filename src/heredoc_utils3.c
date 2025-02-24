/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:14:49 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/24 15:28:34 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_env_vars_in_line(t_minishell *mini, char *line)
{
	char	*result;
	int		pos;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	pos = find_next_env(line);
	while (pos != -1)
	{
		result = append_expanded_env(mini, result, &line, pos);
		pos = find_next_env(line);
	}
	result = ft_strjoin_free(result, line);
	return (result);
}

void	check_hd_expand(char **line, t_minishell *mini)
{
	char	*new_line;

	new_line = expand_env_vars_in_line(mini, *line);
	*line = new_line;
}

void	handle_heredoc_child(t_heredoc *tmp_hd, t_minishell *mini)
{
	int	status;

	if (g_exit_code == 130)
		exit(130);
	set_signals_to_here_doc();
	status = fill_fd_heredoc(tmp_hd, mini);
	if (status == -1)
		perror("Error handling heredoc");
	if (mini->commands->fd[0] != -1)
		close(mini->commands->fd[0]);
	exit (0);
}

int	has_heredoc(t_minishell *mini)
{
	t_node	*tmp;

	tmp = mini->commands->tokens;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	init_heredoc(t_minishell *mini)
{
	mini->heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (check_malloc(mini->heredoc))
		return ;
	mini->heredoc->index = 0;
	mini->heredoc->count_hd = 0;
	mini->heredoc->fd_heredoc_path = NULL;
	mini->heredoc->eof = NULL;
	mini->heredoc->eof = false;
	mini->heredoc->eof_quote = false;
	mini->heredoc->next = NULL;
}
