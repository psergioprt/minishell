/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 07:33:17 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/30 08:39:13 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_file(const char *filename, t_type type)
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

int	handle_redirections(t_minishell *mini)
{
	int		fd;
	t_node	*current;

	current = mini->tokenlst;
	fd = -1;
	while (current)
	{
		if ((current->type != NONE && current->type != PIPE) && \
				current->target != NULL)
		{
			fd = open_file(current->target, current->type);
			if (fd == -1)
			{
				perror("Failed to open file");
				return (-1);
			}
			if (current->type == OUTPUT || current->type == APPEND_OUTPUT)
			{
				if (dup2(fd, STDOUT_FILENO) == -1)
				{
					perror("dup2");
					close(fd);
					return (-1);
				}
				fflush(stdout);
			}
			else if (current->type == INPUT || current->type == HEREDOC)
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
}

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

void	handle_redirectional(t_minishell *mini, t_parse_context *ctx, \
		int *i, int *j)
{
	char	double_op[3];
	char	single_op[2];
	char	*redir_token;
	int		redir_type;

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

void	skip_redirection_plus_target(t_minishell *mini)
{
	t_node	*prev;
	t_node	*current;
	t_node	*tmp;
	t_node	*target_node;

	prev = NULL;
	current = mini->tokenlst;
	while (current)
	{
		if (current->type != NONE && current->type != PIPE)
		{
			tmp = current;
			current = current->next;
			if (current)
			{
				target_node = current;
				current = current->next;
				free(target_node->token);
				free(target_node);
			}
			free(tmp->token);
			free(tmp);
			if (prev)
				prev->next = current;
			else
				mini->tokenlst = current;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	current = mini->tokenlst;
}
