/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_malformed_operators.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:44:23 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/22 22:44:23 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	skip_spaces_and_check_pipe(t_minishell *mini, const char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || \
		(input[*i] >= 9 && input[*i] <= 13)))
		(*i)++;
	if (!input[*i] || input[*i] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|`\n", 2);
		mini->has_error = true;
		mini->exit_status = 2;
		return (true);
	}
	return (false);
}

bool	handle_redirection(t_minishell *mini, const char *input, int *i)
{
	(*i)++;
	if (input[*i] && (input[*i] == '>' || input[*i] == '<'))
		(*i)++;
	if (skip_spaces_and_check_pipe(mini, input, i))
		return (true);
	return (false);
}

bool	handle_pipe(t_minishell *mini, const char *input, int *i)
{
	(*i)++;
	if (skip_spaces_and_check_pipe(mini, input, i))
		return (true);
	if (input[*i] == '<' || input[*i] == '>')
		return (handle_redirection(mini, input, i));
	return (false);
}

bool	check_malformed_operators(t_minishell *mini, t_parse_context *ctx)
{
	int	i;

	i = 0;
	while (ctx->input[i])
	{
		if (ctx->input[i] == '>' || ctx->input[i] == '<')
		{
			if (handle_redirection(mini, ctx->input, &i))
				return (true);
		}
		else if (ctx->input[i] == '|')
		{
			if (handle_pipe(mini, ctx->input, &i))
				return (true);
		}
		i++;
	}
	return (false);
}
