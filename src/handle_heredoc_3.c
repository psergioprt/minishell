/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:08:49 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/10 10:13:43 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	initialize_heredoc(t_minishell *mini, t_node *tmp)
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
		perror("Error: HEREDOC delimiter is NULL");
}

void	append_heredoc(t_minishell *mini, t_node *tmp)
{
	t_heredoc	*tmp_hd;

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
		perror("Error: HEREDOC delimiter is NULL");
}

void	save_heredoc_info(t_minishell *mini)
{
	t_node	*tmp;

	tmp = mini->tokenlst;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->next)
		{
			if (!mini->heredoc)
				initialize_heredoc(mini, tmp);
			else if (!mini->heredoc->eof)
				mini->heredoc->eof = ft_strdup(tmp->next->token);
			else
				append_heredoc(mini, tmp);
		}
		tmp = tmp->next;
	}
}
