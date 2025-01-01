/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:48:55 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/01 19:27:04 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*create_command_node(const char *token)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->token = NULL;
	new_node->next = NULL;
	if (!new_node)
	{
		perror("Error! Failed to allocate memory for new_node\n");
		return (NULL);
	}
	new_node->token = ft_strdup(token);
	if (!new_node->token)
	{
		perror("Error! Failed to duplicate command\n");
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	add_command_node(t_minishell *mini, const char *token)
{
	t_node	*new_node;
	t_node	*current;

	if (!mini || !token)
	{
		perror("Error: add_command_node called with NULL mini or command\n");
		return ;
	}
	new_node = create_command_node(token);
	if (!new_node)
	{
		perror("Error: Failed to create new node\n");
		return ;
	}
	if (!mini->tokelst)
		mini->tokelst = new_node;
	else
	{
		current = mini->tokelst;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

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
void	handle_pipes(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	char	delimeter[2];

	if (*j > 0)
	{
		ctx->current_token[*j] = '\0';
		add_command_node(mini, ctx->current_token);
		*j = 0;
	}
	delimeter[0] = ctx->input[*i];
	delimeter[1] = '\0';
	add_command_node(mini, delimeter);
}

void	handle_open_close_quotes(t_parse_context *ctx, int *i, int *j)
{
	char	quote_char;

	quote_char = ctx->input[*i];
	if (!ctx->quote)
	{
		ctx->quote = quote_char;
		(*i)++;
		while (ctx->input[*i] && ctx->input[*i] != ctx->quote)
			ctx->current_token[(*j)++] = ctx->input[(*i)++];
		if (ctx->input[*i] == ctx->quote)
			ctx->quote = 0;
		else
		{
			printf("Error: Unclosed quote detected!\n");
			exit(1);
		}
	}
}

void	handle_spaces_quotes(t_minishell *mini, const char *input, \
		t_token_context *tok_ctx)
{
	if (!tok_ctx->ctx->quote && input[*tok_ctx->i] == ' ')
	{
		while (input[*tok_ctx->i + 1] == ' ')
			(*tok_ctx->i)++;
		if (input[*tok_ctx->i + 1] == '"' || input[*tok_ctx->i + 1] == '\'')
			return ;
		if (*tok_ctx->j > 0)
		{
			tok_ctx->current_token[*tok_ctx->j] = '\0';
			add_command_node(mini, tok_ctx->current_token);
			*tok_ctx->j = 0;
		}
	}
	else if (input[*tok_ctx->i] == '"' || input[*tok_ctx->i] == '\'')
		handle_open_close_quotes(tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else
	{
		tok_ctx->current_token[*tok_ctx->j] = input[*tok_ctx->i];
		(*tok_ctx->j)++;
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
		mini->has_pipe = true;
		handle_pipes(mini, tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	}
	else if (input[*tok_ctx->i] == '"' || input[*tok_ctx->i] == '\'')
		handle_open_close_quotes(tok_ctx->ctx, tok_ctx->i, tok_ctx->j);
	else
		tok_ctx->current_token[(*tok_ctx->j)++] = input[*tok_ctx->i];
}

void	split_and_add_commands(t_minishell *mini, const char *input)
{
	int				i;
	int				j;
	char			current_token[1024];
	t_parse_context	ctx;
	t_token_context	tok_ctx;

	i = 0;
	j = 0;
	tok_ctx.current_token = current_token;
	tok_ctx.i = &i;
	tok_ctx.j = &j;
	tok_ctx.ctx = &ctx;
	init_variables(mini, &ctx, input, current_token);
	while (input[i])
	{
		handle_loop_parsers(mini, input, &tok_ctx);
		i++;
	}
	if (j > 0)
	{
		current_token[j] = '\0';
		add_command_node(mini, current_token);
	}
}
