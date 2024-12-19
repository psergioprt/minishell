/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:48:55 by pauldos-          #+#    #+#             */
/*   Updated: 2024/12/19 09:27:33 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*create_command_node(const char *token)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
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

//function created to check delimeters characters
static int	is_delimeter(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

//function created to handle redirectinal signs
void	handle_redirectional(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
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

//function created to handle quotes, if opened and closed
void	handle_open_close_quotes(t_parse_context *ctx, int *i, int *j)
{
	if (!ctx->quote)
	{
		ctx->quote = ctx->input[*i];
		(*i)++;
		while (ctx->input[*i] && ctx->input[*i] != ctx->quote)
			ctx->current_token[(*j)++] = ctx->input[(*i)++];
		if (ctx->input[*i] == ctx->quote)
			ctx->quote = 0;
		else
		{
			printf("Error: Unclosed quote detected!\n");
			return ;
		}
	}
}

void	split_and_add_commands(t_minishell *mini, const char *input)
{
	int			i;
	int			j;
	char		current_token[1024];
	char		quote;
	t_parse_context	ctx = {current_token, input, 0};
	mini->has_pipe = false;
	/*ctx.current_token = current_token;
	ctx.current_token = malloc(1024);
	if (!ctx.current_token)
		return ;
	ctx.input = input;
	ctx.index = 0;*/
	i = 0;
	j = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote && input[i] == ' ')
		{
			if (input[i + 1] == ' ' || input[i + 1] == '"' || \
					input[i + 1] == '\'')
			{
				i++;
				continue ;
			}
			if (j > 0)
			{
				current_token[j] = '\0';
				add_command_node(mini, current_token);
				j = 0;
			}
		}
		else if (!quote && (input[i] == '>' || input[i] == '<'))
			handle_redirectional(mini, &ctx, &i, &j);
		else if (!quote && input[i] == '|')
		{
			mini->has_pipe = true;
			handle_pipes(mini, &ctx, &i, &j);
		}
		else if (input[i] == '"' || input[i] == '\'')
			handle_open_close_quotes(&ctx, &i, &j);
		else
			current_token[j++] = input[i];
		i++;
	}
	if (j > 0)
	{
		current_token[j] = '\0';
		add_command_node(mini, current_token);
	}
}

//function created to tokenize
char	*ft_strtok(char *str, const char *delim)
{
	static char	*cur = NULL;
	char		*token_start;
	char		*result;

	if (str != NULL)
		cur = str;
	if (cur == NULL || *cur == '\0')
		return (NULL);
	while (*cur && is_delimeter(*cur, delim))
		cur++;
	if (*cur == '\0')
		return (NULL);
	token_start = cur;
	while (*cur && !is_delimeter(*cur, delim))
		cur++;
	if (*cur)
		*cur++ = '\0';
	result = ft_strdup(token_start);
	return (result);
}

//function created to free the linked list
void	free_list(t_minishell *mini)
{
	t_node	*current;
	t_node	*next;

	current = mini->tokelst;
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
	mini->tokelst = NULL;
}
