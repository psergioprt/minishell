/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:31:03 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/18 19:27:23 by jcavadas         ###   ########.fr       */
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
		ft_putstr_fd(": no such file or directory\n", 2); //TODO O PROBLEMA E QUE ESTA A ENTRAR AQUI PARA O 2 E DEPOIS DA ERRO E SAI NO CAT<<1<<2
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

int	handle_redirections(t_minishell *mini)
{
	int		fd;
	t_cmd	*cmd;
	t_node	*current;

	cmd = mini->commands;
	current = cmd->tokens;
	fd = -1;
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
