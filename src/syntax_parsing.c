/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:11:51 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/20 00:29:38 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//function created to handle redirectinal signs
void	handle_redirectional(t_minishell *mini, t_parse_context *ctx, \
		int *i, int *j)
{
	char	double_op[3];
	char	single_op[2];

	if (*j > 0)
	{
		ctx->current_token[*j] = '\0';
		add_command_node(mini, ctx->current_token);
		*j = 0;
	}
	if (ctx->input[(*i) + 1] == ctx->input[*i])
	{
		double_op[0] = ctx->input[*i];
		double_op[1] = ctx->input[(*i) + 1];
		double_op[2] = '\0';
		add_command_node(mini, double_op);
		(*i)++;
	}
	else
	{
		single_op[0] = ctx->input[*i];
		single_op[1] = '\0';
		add_command_node(mini, single_op);
	}
}

//function created to handle pipes delimeter
void	handle_sep(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	char	sep[2];

	if (*j > 0)
	{
		ctx->current_token[*j] = '\0';
		add_command_node(mini, ctx->current_token);
		*j = 0;
	}
	sep[0] = ctx->input[*i];
	sep[1] = '\0';
	add_command_node(mini, sep);
}

void	process_quoted_content(t_minishell *mini, t_parse_context *ctx, \
		int *i, int *j)
{
	if (ctx->quote == '"' && ctx->input[*i] == '$' && \
		ctx->input[*i + 1] == '\\')
		ctx->current_token[(*j)++] = ctx->input[*i];
	else if (ctx->quote == '"' && ctx->input[*i] == '\\')
	{
		if (ctx->input[*i + 1] == '$' || ctx->input[*i + 1] == '"' || \
				ctx->input[*i + 1] == '\\')
		{
			mini->disable_expand = true;
			(*i)++;
			ctx->current_token[(*j)++] = ctx->input[*i];
		}
		else
			ctx->current_token[(*j)++] = ctx->input[*i];
	}
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

void	handle_open_close_quotes(t_minishell *mini, t_parse_context *ctx, \
		int *i, int *j)
{
	if (!ctx->quote)
	{
		ctx->quote = ctx->input[*i];
		(*i)++;
		if (ctx->input[*i - 1] == '\'')
			mini->disable_expand = true;
		while (ctx->input[*i] && ctx->input[*i] != ctx->quote)
		{
			process_quoted_content(mini, ctx, i, j);
			(*i)++;
		}
		if (ctx->input[*i] == ctx->quote)
			ctx->quote = 0;
		else
		{
			printf("Error: Unclosed quote detected!\n");
			mini->has_error = true;
		}
	}
}

void	handle_spaces_quotes(t_minishell *mini, const char *input, \
		t_token_context *tok_ctx)
{
	char	*expanded_token;

	if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == ' ')
	{
		while (input[*tok_ctx->i + 1] == ' ')
			(*tok_ctx->i)++;
		if (*tok_ctx->j > 0)
		{
			tok_ctx->current_token[*tok_ctx->j] = '\0';
			expanded_token = expand_env_var(tok_ctx->current_token, mini);
			if (mini->disable_expand == true)
				add_command_node(mini, tok_ctx->current_token);
			else
				add_command_node(mini, expanded_token);
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
