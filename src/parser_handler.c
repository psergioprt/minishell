/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:19:39 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/19 15:24:13 by jcavadas         ###   ########.fr       */
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

bool	check_malformed_operators(t_minishell *mini, t_parse_context *ctx)
{
	int	i;

	i = 0;
	while (ctx->input[i])
	{
		if (ctx->input[i] == '>' || ctx->input[i] == '<')
		{
			i++;
			if (ctx->input[i] == '>' || ctx->input[i] == '<')
				i++;
			while (ctx->input[i] && (ctx->input[i] == ' ' || (ctx->input[i] >= 9 && ctx->input[i] <= 13)))
				i++;
			if (ctx->input[i] == '|')
			{
				ft_putstr_fd("syntax error near unexpected token `|`\n", 2);
				mini->has_error = true;
				mini->exit_status = 2;
				return (true);
			}
		}
		i++;
	}
	return (false);
}

void	check_pipes_errors(t_minishell *mini, t_parse_context *ctx)
{
	int	k;
	int	p;
	int	q;

	k = 0;
	while (ctx->input[k])
	{
		if (ctx->input[k] == '|')
		{
			p = k - 1;
			while (p >= 0 && (ctx->input[p] == ' ' || (ctx->input[p] >= 9 && ctx->input[p] <= 13)))
				p--;
			if (p < 0)
			{
				//ft_putstr_fd("OwO\n", 2);
				print_pipes_errors(mini);
				return ;
			}
			q = k + 1;
			while (ctx->input[q] && (ctx->input[q] == ' ' || (ctx->input[q] >= 9 && ctx->input[q] <= 13)))
				q++;
			if (ctx->input[q] == '\0' || ctx->input[q] == '|')
			{
				print_pipes_errors(mini);
				return ;
			}
		}
		k++;
	}
}

void	handle_pipes(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	int	saved_index;

	check_pipes_errors(mini, ctx);
	check_malformed_operators(mini, ctx);
	mini->has_pipe += 1;
	saved_index = *i;
	(*i)++;
	while (ctx->input[*i])
	{
		if (ctx->input[*i] != ' ' && !(ctx->input[*i] >= 9 \
			&& ctx->input[*i] <= 13))
		{
			*i = saved_index;
			handle_sep(mini, ctx, i, j);
			return ;
		}
		(*i)++;
	}
}

void	handle_loop_parsers(t_minishell *mini, const char *input, \
		t_token_context *tok_ctx)
{
	if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == ' ')
		handle_spaces_quotes(mini, input, tok_ctx);
	else if (!tok_ctx->ctx->quote && (input[*tok_ctx->i] == '>' || \
				input[*tok_ctx->i] == '<'))
		handle_redirectional(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == '|')
		handle_pipes(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else if (input[*tok_ctx->i] == '"' || input[*tok_ctx->i] == '\'')
		handle_open_close_quotes(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == '\\')
	{
		mini->disable_expand = true;
		if (input[*tok_ctx->i + 1])
			tok_ctx->current_token[(*tok_ctx->j)++] = input[*tok_ctx->i + 1];
		(*tok_ctx->i)++;
	}
	else if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == '$' && mini->disable_expand && !mini->is_heredoc)
	{
		mini->disable_expand = false;
		handle_env_var(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	}
	else if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == '$' \
			&& !mini->disable_expand)
		handle_env_var(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else
		tok_ctx->current_token[(*tok_ctx->j)++] = input[*tok_ctx->i];
}
