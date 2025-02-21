/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_check_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:58:28 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/21 14:58:28 by jcavadas         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (ctx->input[i] && (ctx->input[i] == ' ' \
				|| (ctx->input[i] >= 9 && ctx->input[i] <= 13)))
		i++;
	return (ctx->input[i] == '|');
}

bool	has_trailing_or_double_pipe(t_parse_context *ctx)
{
	int	i;
	int	j;

	i = 0;
	while (ctx->input[i])
	{
		if (ctx->input[i] == '|')
		{
			j = i + 1;
			while (ctx->input[j] && (ctx->input[j] == ' ' \
						|| (ctx->input[j] >= 9 && ctx->input[j] <= 13)))
				j++;
			if (ctx->input[j] == '\0' || ctx->input[j] == '|')
				return (true);
		}
		i++;
	}
	return (false);
}

void	check_pipes_errors(t_minishell *mini, t_parse_context *ctx)
{
	if (has_leading_pipe(ctx) || has_trailing_or_double_pipe(ctx))
		print_pipes_errors(mini);
}
