/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 23:31:33 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/11 23:21:08 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	mini->is_single_quote = false;
	mini->has_error = false;
}

void	cleanup_readline(void)
{
	rl_clear_history();
	rl_free_line_state();
	rl_deprep_terminal();
	rl_cleanup_after_signal();
}

void	print_envvar(t_minishell *mini)
{
	t_env	*current;

	current = mini->envvars;
	while (current)
	{
		printf("Key: %s, Value: %s\n", current->key, current->value);
		current = current->next;
	}
}
