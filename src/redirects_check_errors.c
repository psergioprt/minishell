/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_check_errors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:09 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/10 18:22:13 by pauldos-         ###   ########.fr       */
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
		printf("bash: syntax error near unexpected token 'newline'\n");
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
		printf("bash: syntax error near unexpected token 'newline'\n");
		mini->has_error = true;
		return (-1);
	}
	else
		return (0);
	return (0);
}

int	check_redirect_errors_support_1(t_minishell *mini)
{
	printf("bash: syntax error near unexpected token 'newline'\n");
	mini->has_error = true;
	return (-1);
}

int	check_redirect_errors(t_minishell *mini)
{
	if (!mini->tokenlst || !mini->tokenlst->token)
		return (-1);
	if (!ft_strncmp(mini->tokenlst->token, ">", 1) || \
			!ft_strncmp(mini->tokenlst->token, ">>", 2) || \
			!ft_strncmp(mini->tokenlst->token, "<", 1) || \
			!ft_strncmp(mini->tokenlst->token, "<<", 2))
	{
		if (!mini->tokenlst->next)
			check_redirect_errors_support_1(mini);
		else if (mini->tokenlst->next)
			handle_redirections(mini);
		else
			skip_redirection_plus_target(mini);
	}
	else if ((ft_strncmp(mini->tokenlst->token, ">", 1) || \
		ft_strncmp(mini->tokenlst->token, ">>", 2) || \
		ft_strncmp(mini->tokenlst->token, "<", 1) || \
		ft_strncmp(mini->tokenlst->token, "<<", 2)) && \
		mini->tokenlst->next)
	{
		return (check_redirect_errors_support(mini));
	}
	return (0);
}
