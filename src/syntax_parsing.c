/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:57:39 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/22 18:57:39 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_quoted_content(t_minishell *mini, t_parse_context *ctx, int *i, \
	int *j)
{
	if (mini->disable_expand == true && ctx->input[*i] == '$')
		ctx->current_token[(*j)++] = ctx->input[*i];
	else if (ctx->quote == '"' && ctx->input[*i] == '$' && \
			ctx->input[*i + 1] == '\\')
		ctx->current_token[(*j)++] = ctx->input[*i];
	else if (ctx->quote == '"' && ctx->input[*i] == '\\')
		process_quoted_helper(mini, ctx, i, j);
	else if (ctx->quote == '"' && ctx->input[*i] == '$')
	{
		if (*i > 0 && ctx->input[*i - 1] == '\\')
			ctx->current_token[(*j)++] = ctx->input[*i];
		else
			handle_env_var(mini, ctx, i, j);
	}
	else
		ctx->current_token[(*j)++] = ctx->input[*i];
}

void	initialize_quote_handling(t_minishell *mini, t_parse_context *ctx, \
	int *i)
{
	mini->heredoc->eof_quote = true;
	mini->unquoted = false;
	if (!ctx->quote)
	{
		if (ctx->input[*i + 1] == ctx->input[*i])
		{
			add_empty_token(mini);
			(*i) += 1;
			return ;
		}
		ctx->quote = ctx->input[*i];
		(*i)++;
		if (ctx->quote == '\'' || mini->is_heredoc)
			mini->disable_expand = true;
		else if (ctx->quote == '"')
			mini->disable_expand = false;
	}
}

void	process_quotes(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	while (ctx->input[*i] && ctx->input[*i] != ctx->quote)
	{
		process_quoted_content(mini, ctx, i, j);
		(*i)++;
	}
	if (ctx->input[*i] == ctx->quote)
	{
		ctx->quote = 0;
		if (!mini->is_heredoc)
		{
			if (ctx->input[*i] == '"')
				mini->disable_expand = false;
			else if (ctx->input[*i] == '\'')
				mini->disable_expand = true;
		}
	}
	else
	{
		ft_putstr_fd("syntax error near unexpected token 'open quote'\n", 2);
		mini->has_error = true;
		mini->exit_status = 2;
	}
}

void	handle_open_close_quotes(t_minishell *mini, t_parse_context *ctx, \
	int *i, int *j)
{
	initialize_quote_handling(mini, ctx, i);
	if (!ctx->quote)
		return ;
	process_quotes(mini, ctx, i, j);
}

void	handle_spaces_quotes(t_minishell *mini, const char *input, \
	t_token_context *tok_ctx)
{
	char	*expanded_token;

	if (!tok_ctx->ctx->quote && (input[*tok_ctx->i] == ' ' || \
		(input[*tok_ctx->i] >= 9 && input[*tok_ctx->i] <= 13)))
	{
		while (input[*tok_ctx->i + 1] == ' ' || \
			(input[*tok_ctx->i + 1] >= 9 && input[*tok_ctx->i + 1] <= 13))
			(*tok_ctx->i)++;
		if (*tok_ctx->j > 0)
		{
			tok_ctx->current_token[*tok_ctx->j] = '\0';
			expanded_token = expand_env_var(tok_ctx->current_token, mini);
			handle_spaces_helper(mini, expanded_token, tok_ctx);
			if (expanded_token != tok_ctx->current_token)
				free(expanded_token);
			*tok_ctx->j = 0;
			mini->disable_expand = false;
		}
	}
	else if (input[*tok_ctx->i] == '"' || input[*tok_ctx->i] == '\'')
		handle_open_close_quotes(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else
		tok_ctx->current_token[(*tok_ctx->j)++] = input[*tok_ctx->i];
}
