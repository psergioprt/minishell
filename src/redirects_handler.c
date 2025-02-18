/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:31:03 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/18 22:23:36 by jcavadas         ###   ########.fr       */
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
		printf("Unsupported redirection type\n");
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
	{
		/* perror("Failed to open file"); */
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

void skip_hds(t_minishell *mini)
{
    t_node *current;
    t_node *prev;
    t_node *to_free;
    t_node *delimiter;
    int found_heredoc;

    current = mini->commands->tokens;
    prev = NULL;
    found_heredoc = 0;

    while (current)
    {
        if (current->type == HEREDOC)
        {
            if (found_heredoc) // Skip this and the next token
            {
                to_free = current; 
                current = current->next; // Move to the next node

                // If there's a delimiter to remove (the next node), do so
                if (current && current->type != HEREDOC) 
                {
                    delimiter = current;
                    current = current->next; // Move to the next token after the delimiter
                    free(delimiter->token);
                    free(delimiter);
                }

                // Free the HEREDOC token
                free(to_free->token);
                free(to_free);

                // If prev is NULL, we're deleting the first node, so update the head of the list
                if (prev)
                    prev->next = current;
                else
                    mini->commands->tokens = current; // Update head if we deleted the first node

                continue; // Skip the next iteration for the current token (since we removed it)
            }
            else
            {
                found_heredoc = 1; // Keep the first HEREDOC
            }
        }
        // Move to the next node
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

int	identify_redirection_type(char *token)
{
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
