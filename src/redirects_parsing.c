/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:59:01 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/22 18:59:01 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	validate_redir_syntax(t_minishell *mini, t_parse_context *ctx, \
		int *i, char redir)
{
	if (mini->count > 2)
	{
		redir_error_message_2(mini, &redir);
		return (true);
	}
	while (ctx->input[*i] && (ctx->input[*i] == ' ' || (ctx->input[*i] >= 9 && \
					ctx->input[*i] <= 13)))
		(*i)++;
	if (ctx->input[*i] == '\0')
	{
		ft_putstr_fd("syntax error near unexpected token `newline`\n", 2);
		mini->has_error = true;
		mini->exit_status = 2;
		return (true);
	}
	if (ctx->input[*i] == '>' || ctx->input[*i] == '<')
	{
		redir_error_message_1(mini, ctx, i);
		return (true);
	}
	return (false);
}

bool	count_redir_chars(t_minishell *mini, t_parse_context *ctx, int *i, \
		char redir)
{
	mini->count = 0;
	while (ctx->input[*i] && (ctx->input[*i] == '>' || ctx->input[*i] == '<'))
	{
		if (ctx->input[*i] != redir)
		{
			redir_error_message_1(mini, ctx, i);
			return (true);
		}
		mini->count++;
		(*i)++;
	}
	return (validate_redir_syntax(mini, ctx, i, redir));
}

bool	check_redirection_errors(t_minishell *mini, t_parse_context *ctx, \
		int *i)
{
	int		start;
	char	redir;

	start = *i;
	if (ctx->input[*i] != '>' && ctx->input[*i] != '<')
		return (false);
	redir = ctx->input[*i];
	if (count_redir_chars(mini, ctx, i, redir))
		return (true);
	*i = start;
	return (false);
}

void	identify_redir_type(t_minishell *mini, char *redir_token)
{
	int		redir_type;

	if (!redir_token)
	{
		ft_putstr_fd("Error: Null redirection token\n", 2);
		return ;
	}
	redir_type = identify_redirection_type(redir_token);
	if (redir_type != -1)
		add_command_node(mini, redir_token, redir_type, &(mini->prev_node));
	else
		ft_putstr_fd("Error: Invalid redirection operator\n", 2);
}

void	handle_redirectional(t_minishell *mini, t_parse_context *ctx, int *i, \
		int *j)
{
	char	single_op[2];
	char	*redir_token;

	if (check_redirection_errors(mini, ctx, i))
		return ;
	if (*j > 0)
	{
		ctx->current_token[*j] = '\0';
		add_command_node(mini, ctx->current_token, NONE, &(mini->prev_node));
		*j = 0;
	}
	if (ctx->input[(*i)] == '<' && ctx->input[(*i + 1)] == '<')
		mini->is_heredoc = true;
	if (ctx->input[(*i) + 1] == ctx->input[*i])
		handle_double_redir(mini, ctx, i, &redir_token);
	else
	{
		single_op[0] = ctx->input[*i];
		single_op[1] = '\0';
		redir_token = single_op;
	}
	identify_redir_type(mini, redir_token);
}
