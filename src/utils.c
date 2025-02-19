/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:33:38 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/09 15:33:38 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list(t_minishell *mini)
{
	t_node	*current;
	t_node	*next;

	current = mini->tokenlst;
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
	mini->tokenlst = NULL;
}

void	free_envvars(t_minishell *mini)
{
	t_env	*current;
	t_env	*next;

	current = mini->envvars;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	init_variables(t_minishell *mini, t_parse_context *ctx, \
		const char *input, char *current_token)
{
	ctx->current_token = current_token;
	ctx->input = input;
	ctx->index = 0;
	ctx->quote = 0;
	mini->has_pipe = 0;
	mini->disable_expand = false;
	mini->has_error = false;
	mini->prev_node = NULL;
	mini->unquoted = true;
	mini->is_heredoc = false;
	init_heredoc(mini);
}

void	cleanup_fd(t_minishell *mini)
{
	close(mini->saved_stdout);
	close(mini->saved_stdin);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
