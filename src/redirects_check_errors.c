/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_check_errors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:09 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/15 09:40:34 by pauldos-         ###   ########.fr       */
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

/*int	check_last_token(t_minishell *mini)
{
	t_node	*current;
	t_node	*last_token;
	int		token_count;

	last_token = NULL;
	token_count = 0;
	if (!mini->tokenlst)
		return (-1);
	current = mini->tokenlst;
	while (current)
	{
		token_count++;
		last_token = current;
		current = current->next;
	}
	if (last_token && (!ft_strncmp(last_token->token, ">", 1) || \
				!ft_strncmp(last_token->token, ">>", 2) || \
				!ft_strncmp(last_token->token, "<", 1) || \
				!ft_strncmp(last_token->token, "<<", 2)))
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		mini->has_error = true;
		return (-1);
	}
	return (0);
}*/

int	check_redirect_errors(t_minishell *mini)
{
//	char	*token;

	if (!mini->tokenlst || !mini->tokenlst->token)
		return (-1);
//	token = mini->tokenlst->token;
/*	if (mini->unquoted == true)
	{
		if (check_last_token(mini))
			return (-1);*/
		/*if (!ft_strncmp(token, ">", 1) || !ft_strncmp(token, ">>", 2) || \
			!ft_strncmp(token, "<", 1) || !ft_strncmp(token, "<<", 2))
		{
			if (!mini->tokenlst->next)
				check_redirect_errors_support_1(mini);
			else if (mini->tokenlst->next)
				handle_redirections(mini);
			else
				skip_redirection_plus_target(mini);
			}*/
/*			if ((ft_strncmp(token, ">", 1) || ft_strncmp(token, ">>", 2) || \
			ft_strncmp(token, "<", 1) || ft_strncmp(token, "<<", 2)) && \
			mini->tokenlst->next)
			return (check_redirect_errors_support(mini));*/
//	}
	return (0);
}
