/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:19:39 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/14 16:34:19 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_pipes(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	int	saved_index;
	int	k = 0;
	
	while (ctx->input[k] && ctx->input[k] == ' ')
		k++;
	if (ctx->input[k] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token '|'\n", 1);
		mini->has_error = true;
		mini->exit_status = 2;
		return ;
	}
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
	ft_putstr_fd("Error: Pipe sign without further input\n", 2);
	mini->has_error = true;
	mini->exit_status = 2;
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
	else if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == '$' && mini->disable_expand)
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
