/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_name_redir_check_errors.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:52:44 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/21 14:52:44 by jcavadas         ###   ########.fr       */
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

void	redirect_check_errors_2(t_minishell *mini, char *env_var_name)
{
	ft_putstr_fd("$", 2);
	ft_putstr_fd(env_var_name, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	mini->exit_status = 1;
	mini->has_error = true;
}
