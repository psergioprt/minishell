/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:49:37 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/21 15:26:12 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(char *env_name, t_minishell *mini)
{
	t_env	*current;

	if (!env_name || !mini)
		return (NULL);
	current = mini->envvars;
	while (current != NULL)
	{
		if (strcmp(current->key, env_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*expand_env_var(char *token, t_minishell *mini)
{
	char	*expanded_token;
	char	*env_value;
	char	*env_name;

	if (token[0] != '$')
		return (token);
	env_name = ft_strdup(token + 1);
	if (!env_name)
	{
		perror("ft_strdup memory allocation failed");
		return (NULL);
	}
	env_value = get_env_value(env_name, mini);
	free(env_name);
	if (env_value)
	{
		expanded_token = ft_strdup(env_value);
		if (!expanded_token)
		{
			perror("ft_strdup failed");
			return (NULL);
		}
		return (expanded_token);
	}
	return (token);
}

void	parse_env_name(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	int		k;
	char	*env_value;
	char	env_var_name[256];

	k = 0;
	env_value = NULL;
	while (ft_isalnum(ctx->input[*i]) || ctx->input[*i] == '_')
		env_var_name[k++] = ctx->input[(*i)++];
	env_var_name[k] = '\0';
	(*i)--;
	env_value = get_env_value(env_var_name, mini);
	if (env_value)
	{
		ctx->m = 0;
		while (env_value[ctx->m])
			ctx->current_token[(*j)++] = env_value[(ctx->m)++];
	}
	else if (mini->unquoted == false)
		redirect_check_errors(mini);
	else if (mini->prev_node && (!ft_strcmp(mini->prev_node->token, ">") || \
				!ft_strcmp(mini->prev_node->token, "<") || \
				!ft_strcmp(mini->prev_node->token, ">>")))
		redirect_check_errors_2(mini, env_var_name);
}

void	handle_env_var(t_minishell *mini, t_parse_context *ctx, int *i, int *j)
{
	(*i)++;
	if (ctx->input[*i] == '?')
	{
		ctx->exit_status = ft_itoa(mini->exit_status);
		ctx->m = 0;
		while (ctx->exit_status[ctx->m])
			ctx->current_token[(*j)++] = ctx->exit_status[ctx->m++];
	}
	else if (ft_isalnum(ctx->input[*i]) || ctx->input[*i] == '_')
		parse_env_name(mini, ctx, i, j);
	else if (ctx->input[*i] == ' ' || ctx->input[*i] == '\0')
	{
		ctx->current_token[(*j)++] = '$';
		(*i)--;
	}
	else if (ctx->input[*i] == '"' || ctx->input[*i] == '\'')
		(*i)--;
}
