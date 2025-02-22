/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 00:09:35 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/10 00:09:35 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sep(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	char	sep[2];
	int		pipe_type;

	pipe_type = identify_redirection_type((char []){ctx->input[*i], '\0'});
	if (*j > 0)
	{
		ctx->current_token[*j] = '\0';
		add_command_node(mini, ctx->current_token, NONE, &(mini->prev_node));
		*j = 0;
	}
	sep[0] = ctx->input[*i];
	sep[1] = '\0';
	add_command_node(mini, sep, pipe_type, &(mini->prev_node));
}

void	handle_double_redir(t_minishell *mini, t_parse_context *ctx, \
		int *i, char **redir_token)
{
	static char	double_op[3];

	double_op[0] = ctx->input[*i];
	double_op[1] = ctx->input[(*i) + 1];
	double_op[2] = '\0';
	*redir_token = double_op;
	(*i)++;
	if (ft_strcmp(*redir_token, "<<") == 0)
		mini->disable_expand = true;
}

void	process_quoted_helper(t_minishell *mini, t_parse_context *ctx, \
		int *i, int *j)
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

void	handle_spaces_helper(t_minishell *mini, char *expanded_token, \
		t_token_context *tok_ctx)
{
	if (mini->disable_expand == true)
		add_command_node(mini, tok_ctx->current_token, \
			NONE, &(mini->prev_node));
	else
		add_command_node(mini, expanded_token, NONE, \
			&(mini->prev_node));
}
