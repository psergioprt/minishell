/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:11:51 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/28 12:31:45 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_file(const char *filename, t_redirection_type type)
{
	int	fd;
	if (type == OUTPUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND_OUTPUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == INPUT)
		fd = open(filename, O_RDONLY);
	else
	{
		printf("Unsupported redirection type\n");
		return (-1);
	}
	if (fd == -1)
		perror("open");
	return (fd);
}

/*int	handle_redirections(t_minishell *mini)
{
	int	fd;

	t_node *current = mini->tokenlst;
	while (current)
	{
		if (current->redir_type != NONE)
		{
			if (current->redir_type == 1)
			{
				current = current->next;
				if (current && current->token)
					current->target = strdup(current->token);
			}
			fd = open_file(current->target, current->redir_type);
			if (fd == -1)
			{
				printf("Failed to open file: %s\n", current->target);
				return (-1);
			}
			if (current->redir_type == OUTPUT || current->redir_type == APPEND_OUTPUT)
			{
				if (dup2(fd, STDOUT_FILENO) == -1)
				{
					perror("dup2");
					close(fd);
					return (-1);
				}
			}
			else if (current->redir_type == INPUT || current->redir_type == HEREDOC)
			{
				if (dup2(fd, STDIN_FILENO) == -1)
				{
					perror("dup2");
					close(fd);
					return (-1);
				}
			}
			close(fd);
		}
		current = current->next;
	}
	return (0);
}*/

int	handle_redirections(t_minishell *mini)
{
	t_node *current = mini->tokenlst;
	int	fd = -1;
	while (current)
	{
		if (current->redir_type != NONE && current->target != NULL)
		{
			printf("Processing redirection: token='%s', redir_type=%d, target='%s'\n", current->token, current->redir_type, current->target);
			fd = open_file(current->target, current->redir_type);
			if (fd == -1)
			{
				printf("Failed to open file: %s\n", current->target);
				return (-1);
			}
			if (current->redir_type == OUTPUT || current->redir_type == APPEND_OUTPUT)
			{
				if (dup2(fd, STDOUT_FILENO) == -1)
				{
					perror("dup2");
					close(fd);
					return (-1);
				}
				printf("Successfully redirected STDOUT to fd=%d\n", fd);
			}
			else if (current->redir_type == INPUT || current->redir_type == HEREDOC)
			{
				if (dup2(fd, STDIN_FILENO) == -1)
				{
					perror("dup2");
					close(fd);
					return (-1);
				}
				printf("Successfully redirected STDIN to fd=%d\n", fd);
			}
			close(fd);
		}
		current = current->next;
	}
	return 0;
}

//
/*int	handle_redirections(t_minishell *mini)
{
	t_node *current = mini->tokenlst;
	int	fd = -1;
	//int	cur_type;
	
	while (current)
	{
		printf("Processing node: token='%s', redir_type=%d, target='%s'\n", current->token, current->redir_type, current->target);
//		if (current->redir_type != NONE)
//		{
//			cur_type = current->redir_type;
//			current = current->next;
//			if (!current)
//				break;
//			current->redir_type = cur_type;
//		}
		if (current->redir_type != NONE && current->target != NULL)
		{
			printf("target: %s, type: %d\n", current->target, current->redir_type);
			fd = open_file(current->target, current->redir_type);
			if (fd == -1)
			{
				fprintf(stderr, "Failed to open file: %s\n", current->target);
				return -1;
			}
			printf("Processing redirection: token='%s', redir_type=%d\n", current->token, current->redir_type);
			if (current->redir_type == OUTPUT || current->redir_type == APPEND_OUTPUT)
			{
				printf("Entered here\n");
				fflush(stdout);
				if (dup2(fd, STDOUT_FILENO) == -1)
				{
					printf("hello\n");
					perror("dup2");
					close(fd);
					return -1;
				}
				printf("dup2 succeeded: redirected STDOUT to fd=%d\n", fd);
			}
			else if (current->redir_type == INPUT || current->redir_type == HEREDOC)
			{
				if (dup2(fd, STDIN_FILENO) == -1)
				{
					perror("dup2");
					close(fd);
					return -1;
				}
			}
			close(fd);
		}
		current = current->next;
	}
	return 0;
}*/

int	identify_redirection_type(char *token)
{
	printf("Current_token: %s\n", token);
	if (!ft_strcmp(token, ">"))
		return (OUTPUT);
	if (!ft_strcmp(token, ">>"))
		return (APPEND_OUTPUT);
	if (!ft_strcmp(token, "<"))
		return (INPUT);
	if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	return (-1);
}

void    handle_redirectional(t_minishell *mini, t_parse_context *ctx, \
                int *i, int *j)
{
	char    double_op[3];
	char    single_op[2];
	char    *redir_token;
	int     redir_type;
	
	if (*j > 0)
	{
		ctx->current_token[*j] = '\0';
		add_command_node(mini, ctx->current_token, NONE);
		*j = 0;
	}
	if (ctx->input[(*i) + 1] == ctx->input[*i])
	{
		double_op[0] = ctx->input[*i];
		double_op[1] = ctx->input[(*i) + 1];
		double_op[2] = '\0';
		redir_token = double_op;
		(*i)++;
	}
	else
	{
		single_op[0] = ctx->input[*i];
		single_op[1] = '\0';
		redir_token = single_op;
	}
	redir_type = identify_redirection_type(redir_token);
	if (redir_type != -1)
		add_command_node(mini, redir_token, redir_type);
	else
		perror("Error: Invalid redirection operator\n");
}


//function created to handle redirectinal signs
/*void	handle_redirectional(t_minishell *mini, t_parse_context *ctx, \
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
}*/

//function created to handle pipes delimeter
void	handle_sep(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	char	sep[2];

	if (*j > 0)
	{
		ctx->current_token[*j] = '\0';
		add_command_node(mini, ctx->current_token, NONE);
		*j = 0;
	}
	sep[0] = ctx->input[*i];
	sep[1] = '\0';
	add_command_node(mini, sep, NONE);
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
				add_command_node(mini, tok_ctx->current_token, NONE);
			else
				add_command_node(mini, expanded_token, NONE);
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
