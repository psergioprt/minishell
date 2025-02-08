/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:14:49 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/08 21:55:08 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_env_vars_in_line(t_minishell *mini, char *line)
{
	char	*result = ft_strdup("");

	if (!result)
		return (NULL);
	int pos;
	while ((pos = find_next_env(line)) != -1)
	{
		result = append_expanded_env(mini, result, &line, pos);
	}
	result = ft_strjoin_free(result, line);
	//free(line); Comentar isto resovle o double free
	return (result);
}

void	check_hd_expand(char **line, t_minishell *mini)
{
	char	*new_line = expand_env_vars_in_line(mini, *line);
	*line = new_line;
}

void	handle_heredoc_child(t_heredoc *tmp_hd, t_minishell *mini)
{
	int status;

	set_signals_to_here_doc();
	status = fill_fd_heredoc(tmp_hd, mini);
	if (status == -1)
		perror("Error handling heredoc");
	exit (0);
}

int	has_heredoc(t_minishell *mini)
{
	t_node	*tmp = mini->tokenlst;
	while (tmp)
	{
		if(tmp->type == HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
