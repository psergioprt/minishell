/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:19:39 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/28 17:11:48 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_pipes(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	int	saved_index;

	mini->has_pipe += 1;
	saved_index = *i;
	(*i)++;
	while (ctx->input[*i])
	{
		if (ctx->input[*i] != ' ' && !(ctx->input[*i] >= 9 && \
					ctx->input[*i] <= 13))
		{
			*i = saved_index;
			handle_sep(mini, ctx, i, j);
			return ;
		}
		(*i)++;
	}
	printf("Error: Pipe sign without further input\n");
	mini->has_error = true;
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
	else if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == '$')
		handle_env_var(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else
		tok_ctx->current_token[(*tok_ctx->j)++] = input[*tok_ctx->i];
}
