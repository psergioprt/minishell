/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:59:52 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/22 18:59:52 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	redir_error_message_1(t_minishell *mini, t_parse_context *ctx, int *i)
{
	char	error_token[2];

	error_token[0] = ctx->input[*i];
	error_token[1] = '\0';
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd("\n", 2);
	mini->has_error = true;
	mini->exit_status = 2;
	return (true);
}

bool	redir_error_message_2(t_minishell *mini, char *redir)
{
	char	error_token[2];

	error_token[0] = *redir;
	error_token[1] = '\0';
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd("\n", 2);
	mini->has_error = true;
	mini->exit_status = 2;
	return (true);
}
