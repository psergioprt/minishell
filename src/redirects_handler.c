/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:31:03 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/21 12:45:03 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_file(char *filename, t_type type)
{
	int	fd;

	if (type == OUTPUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND_OUTPUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == INPUT || type == HEREDOC)
		fd = open(filename, O_RDONLY);
	else
	{
		ft_putstr_fd("Unsupported redirection type\n", 2);
		return (-1);
	}
	if (fd == -1)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	return (fd);
}

int	handle_redirection_action(int fd, t_node *current)
{
	if (fd == -1)
		return (-1);
	if (current->type == OUTPUT || current->type == APPEND_OUTPUT)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
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
	return (0);
}

void	free_heredoc(t_node **current, t_node **prev, t_minishell *mini)
{
	t_node	*to_free;

	to_free = *current;
	*current = (*current)->next;
	if (*current && (*current)->type != HEREDOC)
	{
		free((*current)->token);
		to_free->next = (*current)->next;
		free(*current);
		*current = to_free->next;
	}
	free(to_free->token);
	free(to_free);
	if (*prev)
		(*prev)->next = *current;
	else
		mini->commands->tokens = *current;
}

void	skip_hds(t_minishell *mini)
{
	t_node	*current;
	t_node	*prev;
	int		found_heredoc;

	current = mini->commands->tokens;
	prev = NULL;
	found_heredoc = 0;
	while (current)
	{
		if (current->type == HEREDOC && found_heredoc)
		{
			free_heredoc(&current, &prev, mini);
			continue ;
		}
		if (current->type == INPUT || current->type == OUTPUT || current->type == APPEND_OUTPUT)
			break ;
		found_heredoc = (current->type == HEREDOC);
		prev = current;
		current = current->next;
	}
}

int	handle_redirections(t_minishell *mini)
{
	int		fd;
	t_cmd	*cmd;
	t_node	*current;

	cmd = mini->commands;
	current = cmd->tokens;
	fd = -1;
	skip_hds(mini);
	while (current)
	{
		if ((current->type != NONE && current->type != PIPE) && \
				current->target != NULL)
		{
			fd = open_file(current->target, current->type);
			if (fd == -1)
				return (-1);
			if (handle_redirection_action(fd, current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
