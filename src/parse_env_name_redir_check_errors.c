/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_name_redir_check_errors.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:32:50 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/21 08:35:57 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirect_check_errors(t_minishell *mini)
{
	if (mini->prev_node && (!ft_strcmp(mini->prev_node->token, ">") || \
				!ft_strcmp(mini->prev_node->token, "<") || \
				!ft_strcmp(mini->prev_node->token, ">>")))
	{
		ft_putstr_fd("No such file or directory\n", 2);
		mini->exit_status = 1;
		mini->has_error = true;
	}
	add_empty_token(mini);
}

void	redirect_check_errors_2(t_minishell *mini)
{
	ft_putstr_fd("ambiguos redirect\n", 2);
	mini->exit_status = 1;
	mini->has_error = true;
}
