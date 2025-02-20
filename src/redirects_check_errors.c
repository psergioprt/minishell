/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_check_errors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:09 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/20 18:03:00 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_redirect_errors_support(t_minishell *mini)
{
	if (((!ft_strncmp(mini->tokenlst->next->token, ">", 1) || \
		!ft_strncmp(mini->tokenlst->next->token, ">>", 2) || \
		!ft_strncmp(mini->tokenlst->next->token, "<", 1) || \
		!ft_strncmp(mini->tokenlst->next->token, "<<", 2)) && \
		!mini->tokenlst->next->next))
	{
		ft_putstr_fd("bash: syntax error near unexpected token 'newline'\n", 2);
		mini->has_error = true;
		return (-1);
	}
	if (((mini->tokenlst->next->next && \
		(!ft_strncmp(mini->tokenlst->next->next->token, ">", 1) \
		|| !ft_strncmp(mini->tokenlst->next->next->token, ">>", 2) \
		|| !ft_strncmp(mini->tokenlst->next->next->token, "<", 1) || \
		!ft_strncmp(mini->tokenlst->next->next->token, "<<", 2)) && \
		!mini->tokenlst->next->next->next)))
	{
		ft_putstr_fd("bash: syntax error near unexpected token 'newline'\n", 2);
		mini->has_error = true;
		return (-1);
	}
	else
		return (0);
	return (0);
}

int	check_redirect_errors_support_1(t_minishell *mini)
{
	ft_putstr_fd("bash: syntax error near unexpected token 'newline'\n", 2);
	mini->has_error = true;
	return (-1);
}

int	check_redirect_errors(t_minishell *mini)
{
	if (!mini->tokenlst || !mini->tokenlst->token)
		return (-1);
	return (0);
}
