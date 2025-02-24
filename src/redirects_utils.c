/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:55:03 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/24 15:03:48 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_targets(t_minishell *mini)
{
	t_cmd		*cmd;
	t_node		*token;
	t_heredoc	*tmp_hd;

	cmd = mini->commands;
	tmp_hd = mini->heredoc;
/* 	while (cmd)
	{ */
		token = cmd->tokens;
		while (token)
		{
			if (token->type == HEREDOC)
			{
				token->target = ft_strdup(tmp_hd->fd_heredoc_path);
				if (tmp_hd->next)
					tmp_hd = tmp_hd->next;
			}
			token = token->next;
		}
		cmd = cmd->next;
	//}
}

