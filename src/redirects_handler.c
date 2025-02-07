/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:31:03 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/07 12:12:20 by jcavadas         ###   ########.fr       */
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
	else if (type == INPUT || type == HEREDOC) //HEREDOC UPDATED
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
	//printf("Current_token: %s\n", token);
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

void skip_redirection_plus_target_cmd(t_cmd *cmd_list)
{
	t_cmd  *cmd;
	t_node *prev;
	t_node *current;
	t_node *tmp;
	t_node *target_node;

	cmd = cmd_list;
	while (cmd)
	{
		prev = NULL;
		current = cmd->tokens;
		while (current)
		{
			if (current->type != NONE && current->type != HEREDOC && current->type != PIPE)
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
					cmd->tokens = current;
			}
			else
			{
				prev = current;
				current = current->next;
			}
		}
		cmd = cmd->next;
	}
}

void	skip_redirection_plus_target(t_minishell *mini)
{
	t_node	*prev;
	t_node	*current;
	t_node	*tmp;
	t_node	*target_node;

	prev = NULL;
	current = mini->tokenlst;
	skip_redirection_plus_target_cmd(mini->commands);
	while (current)
	{
		if (current->type != NONE && current->type != HEREDOC && current->type != PIPE)
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

int	check_redirect_errors(t_minishell *mini)
{
	if (!mini->tokenlst || !mini->tokenlst->token)
		return (-1);
	if (!ft_strncmp(mini->tokenlst->token, ">", 1) || \
			!ft_strncmp(mini->tokenlst->token, ">>", 2) || \
			!ft_strncmp(mini->tokenlst->token, "<", 1) || \
			!ft_strncmp(mini->tokenlst->token, "<<", 2))
	{
		if (!mini->tokenlst->next)
		{
			perror("minishell: syntax error near unexpected token 'newline'");
			mini->has_error = true;
			return (-1);
		}
		else if (mini->tokenlst->next /*&& !mini->tokenlst->next->next*/)
			handle_redirections(mini);
		else
			skip_redirection_plus_target(mini);
	}
	else if ((ft_strncmp(mini->tokenlst->token, ">", 1) || \
				 ft_strncmp(mini->tokenlst->token, ">>", 2) || \
				 ft_strncmp(mini->tokenlst->token, "<", 1) || \
				 ft_strncmp(mini->tokenlst->token, "<<", 2)) && \
			 mini->tokenlst->next)
	{
		if (((!ft_strncmp(mini->tokenlst->next->token, ">", 1) || \
						!ft_strncmp(mini->tokenlst->next->token, ">>", 2) || \
						!ft_strncmp(mini->tokenlst->next->token, "<", 1) || \
						!ft_strncmp(mini->tokenlst->next->token, "<<", 2))  && \
					!mini->tokenlst->next->next))
		{
			perror("minishell: syntax error near unexpected token 'newline'");
			mini->has_error = true;
			return (-1);
		}
		else
			return (0);
	}
	return (0);
}
