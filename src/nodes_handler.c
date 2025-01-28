/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:48:55 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/27 23:12:55 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*create_command_node(const char *token, t_redirection_type redir_type, t_node **prev_node)
{
	t_node *new_node;
	
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
	new_node->redir_type = redir_type;
	new_node->target = NULL;
	new_node->next = NULL;
	if (prev_node && *prev_node)
	{
		t_node *prev = *prev_node;
		if (prev->redir_type != NONE && prev->target == NULL)
		{
			prev->target = ft_strdup(token);
			printf("Assigned target '%s' to node with token '%s'\n", prev->target, prev->token);
		}
	}
	if (prev_node)
		*prev_node = new_node;
	printf("Node created: token='%s', redir_type=%d, target='%s'\n", new_node->token, new_node->redir_type, new_node->target/*new_node->target ? new_node->target : "(null)"*/);
	return (new_node);
}

/*t_node	*create_command_node(const char *token, t_redirection_type redir_type, const char *target)
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
	new_node->redir_type = redir_type;
	if (target)
	{
		new_node->target = ft_strdup(target);
		if (!new_node->target)
		{
			perror("Error! Failed to duplicate target\n");
			free(new_node->token);
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->target = NULL;
	new_node->next = NULL;
	printf("Target: %s, Redir_type: %d\n", new_node->target, new_node->redir_type);
	return (new_node);
}*/

void	add_command_node(t_minishell *mini, const char *token, t_redirection_type redir_type) //ADDED t_redirection_type
{
	t_node	*new_node;
	t_node	*current;
	static t_node	*prev_node = NULL; //ADDED THIS VARIABLE

	if (!mini || !token)
	{
		perror("Error: add_command_node called with NULL mini or command\n");
		return ;
	}
	new_node = create_command_node(token, redir_type, &prev_node);
	if (!new_node)
	{
		perror("Error: Failed to create new node\n");
		return ;
	}
	if (!mini->tokenlst)
		mini->tokenlst = new_node;
	else
	{
		current = mini->tokenlst;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

//ORIGINAL FUNCTIONS BEFORE REDIRECTS
/*t_node	*create_command_node(const char *token)
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
	if (!mini->tokenlst)
		mini->tokenlst = new_node;
	else
	{
		current = mini->tokenlst;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}*/

void	handle_command_addition(t_minishell *mini, int *j)
{
	char	*expanded_token;

	expanded_token = NULL;
	if (*j > 0 && !mini->has_error)
	{
		mini->current_token[*j] = '\0';
		expanded_token = expand_env_var(mini->current_token, mini);
		if (mini->disable_expand)
			add_command_node(mini, mini->current_token, NONE);
		else
			add_command_node(mini, expanded_token, NONE);
		if (expanded_token != mini->current_token)
			free(expanded_token);
		mini->disable_expand = false;
	}
}

void	split_and_add_commands(t_minishell *mini, const char *input)
{
	int				i;
	int				j;
	t_parse_context	ctx;
	t_token_context	tok_ctx;

	i = 0;
	j = 0;
	tok_ctx.current_token = mini->current_token;
	tok_ctx.i = &i;
	tok_ctx.j = &j;
	tok_ctx.ctx = &ctx;
	init_variables(mini, &ctx, input, mini->current_token);
	while (input[i])
	{
		handle_loop_parsers(mini, input, &tok_ctx);
		if (!mini->has_error)
			i++;
	}
	handle_command_addition(mini, &j);
}
