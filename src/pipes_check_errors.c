/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_check_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:27:05 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/20 22:41:24 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_pipes_errors(t_minishell *mini)
{
	ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
	mini->has_error = true;
	mini->exit_status = 2;
	return ;
}

bool	has_leading_pipe(t_parse_context *ctx)
{
	int	p;

	p = 0;
	while (ctx->input[p] && (ctx->input[p] == ' ' \
				|| (ctx->input[p] >= 9 && ctx->input[p] <= 13)))
		p++;
	return (ctx->input[p] == '|');
}

bool	has_trailing_or_double_pipe(t_parse_context *ctx)
{
	int	k;
	int	q;

	k = 0;
	while (ctx->input[k])
	{
		if (ctx->input[k] == '|')
		{
			q = k + 1;
			while (ctx->input[q] && (ctx->input[q] == ' ' \
						|| (ctx->input[q] >= 9 && ctx->input[q] <= 13)))
				q++;
			if (ctx->input[q] == '\0' || ctx->input[q] == '|')
				return (true);
		}
		k++;
	}
	return (false);
}

void	check_pipes_errors(t_minishell *mini, t_parse_context *ctx)
{
	if (has_leading_pipe(ctx) || has_trailing_or_double_pipe(ctx))
		print_pipes_errors(mini);
}
