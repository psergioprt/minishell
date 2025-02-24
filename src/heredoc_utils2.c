/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:12:26 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/24 11:48:57 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_heredoc_list(t_minishell *mini)
{
	t_heredoc	*tmp_hd;

	while (mini->heredoc)
	{
		tmp_hd = mini->heredoc;
		mini->heredoc = mini->heredoc->next;
		tmp_hd->done = false;
		tmp_hd->targeted = false;
		if (tmp_hd->fd_heredoc_path)
			unlink(tmp_hd->fd_heredoc_path);
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
	t_node		*tmp_token;
	t_heredoc	*tmp_hd;

	tmp_token = mini->commands->tokens;
	tmp_hd = mini->heredoc;
	while (tmp_token)
	{
		if (tmp_token->type == HEREDOC)
		{
			while (tmp_hd)
			{
				tmp_token->type = HEREDOC;
				if (!tmp_hd->targeted)
					tmp_token->target = tmp_hd->fd_heredoc_path;
				tmp_hd->targeted = true;
				tmp_hd = tmp_hd->next;
			}
		}
		tmp_token = tmp_token->next;
	}
}

int	find_next_env(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

static char	*handle_variable_expansion(char *result, t_minishell *mini, \
		char *vartoken)
{
	char	*expanded;
	char	*tmp;

	expanded = expand_env_var(vartoken, mini);
	if (expanded && expanded[0] != '$')
	{
		tmp = ft_strjoin_free(result, expanded);
		free(expanded);
		result = tmp;
	}
	else
	{
		tmp = ft_strjoin_free(result, " ");
		free(expanded);
		result = tmp;
	}
	return (result);
}

char	*append_expanded_env(t_minishell *mini, char *result, char **pline, \
		int pos)
{
	char	*before;
	char	*vartoken;
	char	*rest;
	int		j;

	before = ft_substr(*pline, 0, pos);
	if (!before)
		return (result);
	result = ft_strjoin_free(result, before);
	free(before);
	j = pos + 1;
	while ((*pline)[j] && (ft_isalnum((*pline)[j]) || (*pline)[j] == '_'))
		j++;
	vartoken = ft_substr(*pline, pos, j - pos);
	if (!vartoken)
		return (result);
	result = handle_variable_expansion(result, mini, vartoken);
	free(vartoken);
	rest = ft_strdup(*pline + j);
	if (!rest)
		return (result);
	free(*pline);
	*pline = rest;
	return (result);
}
