/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:19:39 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/20 00:21:01 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_escape_character(t_minishell *mini, const char *input, \
		t_token_context *tok_ctx)
{
	if (input[*tok_ctx->i + 1] && (input[*tok_ctx->i + 1] == '$' || \
				input[*tok_ctx->i + 1] == '\\' || input[*tok_ctx->i + 1] \
				== ' ' || input[*tok_ctx->i + 1] == '\t'))
	{
		mini->disable_expand = true;
		tok_ctx->current_token[(*tok_ctx->j)++] = input[*tok_ctx->i + 1];
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
	{
		mini->has_pipe += 1;
		handle_sep(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	}
	else if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == ';')
		handle_sep(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else if (input[*tok_ctx->i] == '"' || input[*tok_ctx->i] == '\'')
		handle_open_close_quotes(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == '\\')
	{
		handle_escape_character(mini, input, tok_ctx);
		(*tok_ctx->i)++;
	}
	else if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == '$')
		handle_env_var(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else
		tok_ctx->current_token[(*tok_ctx->j)++] = input[*tok_ctx->i];
}
