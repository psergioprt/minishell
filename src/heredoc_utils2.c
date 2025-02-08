/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:12:26 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/08 14:24:13 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_heredoc(t_minishell *mini)
{
	mini->heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (check_malloc(mini->heredoc))
		return;
	mini->heredoc->index = 0;
	mini->heredoc->count_hd = 0;
	mini->heredoc->fd_heredoc_path = NULL;
	mini->heredoc->eof = NULL;
	mini->heredoc->eof_quote = false;
	mini->heredoc->next = NULL;
}

void	clear_heredoc_list(t_minishell *mini)
{
	t_heredoc *tmp_hd;
	while (mini->heredoc)
	{
		tmp_hd = mini->heredoc;
		mini->heredoc = mini->heredoc->next;
		if (tmp_hd->fd_heredoc_path)
			free(tmp_hd->fd_heredoc_path);
		if (tmp_hd->eof)
			free(tmp_hd->eof);
		free(tmp_hd);
	}
	mini->heredoc = NULL;
}

void	include_hd_path(t_minishell *mini)
{
	t_node	*tmp_token = mini->tokenlst;
	t_heredoc	*tmp_hd = mini->heredoc;
	
	while (tmp_token)
	{
		if (tmp_token->type == HEREDOC)
		{
			tmp_token->type = INPUT;
			tmp_token->target = tmp_hd->fd_heredoc_path;
			tmp_hd = tmp_hd->next;
		}
		tmp_token = tmp_token->next;
	}
}

int	find_next_env(char *line)
{
	int	i = 0;

	while (line[i])
	{
		if (line[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*append_expanded_env(t_minishell *mini, char *result, char **pline, int pos)
{
	char	*before;
	int	j;
	char	*varToken;
	char	*expanded;
	char 	*rest;
	
	before = ft_substr(*pline, 0, pos);
	result = ft_strjoin_free(result, before);
	free(before);
	j = pos + 1;
	while ((*pline)[j] && (ft_isalnum((*pline)[j]) || (*pline)[j] == '_'))
			j++;
	varToken = ft_substr(*pline, pos, j - pos);
	expanded = expand_env_var(varToken, mini);
	free(varToken);
	result = ft_strjoin_free(result, expanded);
	free(expanded);
	rest = ft_strdup(*pline + j);
	free(*pline);
	*pline = rest;
	return (result);
}
