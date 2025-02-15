/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:11:51 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/15 18:53:10 by pauldos-         ###   ########.fr       */
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

bool	redir_error_message_1(t_minishell *mini, t_parse_context *ctx, int *i)
{
	char	error_token[2];

	error_token[0] = ctx->input[*i];
	error_token[1] = '\0';
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd("\n", 2);
	mini->has_error = true;
	mini->exit_status = 2;
	return (true);
}

bool	redir_error_message_2(t_minishell *mini, char *redir)
{
	char	error_token[2];

	error_token[0] = *redir;
	error_token[1] = '\0';
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd("\n", 2);
	mini->has_error = true;
	mini->exit_status = 2;
	return (true);
}

bool	check_redirection_errors(t_minishell *mini, t_parse_context *ctx, \
		int *i)
{
	int		start;
	char	redir;
	int		count;

	start = *i;
	count = 0;
	if (ctx->input[*i] != '>' && ctx->input[*i] != '<')
		return (false);
	redir = ctx->input[*i];
	while (ctx->input[*i] && (ctx->input[*i] == '>' || ctx->input[*i] == '<'))
	{
		if (ctx->input[*i] != redir)
		{
			redir_error_message_1(mini, ctx, i);
			return (true);
		}
		count++;
		(*i)++;
	}
	if (count > 2)
	{
		redir_error_message_2(mini, &redir);
		return (true);
	}
	while (ctx->input[*i] && (ctx->input[*i] == ' ' || (ctx->input[*i] >= 9 \
					&& ctx->input[*i] <= 13)))
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
	*i = start;
	return (false);
}

void	handle_redirectional(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	char	single_op[2];
	char	*redir_token;
	int		redir_type;

	if (check_redirection_errors(mini, ctx, i))
		return ;
	if (*j > 0)
	{
		ctx->current_token[*j] = '\0';
		add_command_node(mini, ctx->current_token, NONE, &(mini->prev_node));
		*j = 0;
	}
	if (ctx->input[(*i) + 1] == ctx->input[*i])
		handle_double_redir(mini, ctx, i, &redir_token);
	else
	{
		single_op[0] = ctx->input[*i];
		single_op[1] = '\0';
		redir_token = single_op;
	}
	redir_type = identify_redirection_type(redir_token);
	if (redir_type != -1)
		add_command_node(mini, redir_token, redir_type, &(mini->prev_node));
	else
		perror("Error: Invalid redirection operator\n");
}

void	process_quoted_content(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
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

void	add_token_to_list(t_minishell *mini, t_node *new_token)
{
	t_node	*current;

	if (!mini->tokenlst)
		mini->tokenlst = new_token;
	else
	{
		current = mini->tokenlst;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

void	add_empty_token(t_minishell *mini)
{
	t_node	*new_token;

	new_token = malloc(sizeof(t_node));
	check_malloc(new_token);
	new_token->token = strdup("");
	check_malloc(new_token->token);
	new_token->type = NONE;
	new_token->next = NULL;
	add_token_to_list(mini, new_token);
}

void	handle_open_close_quotes(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	mini->heredoc->eof_quote = true;
	mini->unquoted = false;
	if (!ctx->quote)
	{
		if (ctx->input[*i + 1] == ctx->input[*i])
		{
			add_empty_token(mini);
			(*i) += 2;
			return ;
		}
		else
		{
			ctx->quote = ctx->input[*i];
			(*i)++;
			if (ctx->quote == '\'')
				mini->disable_expand = true;
			else if (ctx->quote == '"')
				mini->disable_expand = false;
			while (ctx->input[*i] && ctx->input[*i] != ctx->quote)
			{
				process_quoted_content(mini, ctx, i, j);
				(*i)++;
			}
			if (ctx->input[*i] == ctx->quote)
			{
				ctx->quote = 0;
				if (ctx->input[*i] == '"')
					mini->disable_expand = false;
				else if (ctx->input[*i] == '\'')
					mini->disable_expand = true;
			}
			else
			{
				ft_putstr_fd("syntax error near unexpected token 'open quote'\n", 2);
				mini->has_error = true;
				mini->exit_status = 2;
			}
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
