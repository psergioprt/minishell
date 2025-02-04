/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:38:05 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/08 22:38:05 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_envvars(t_minishell *mini)
{
	t_env	*envvars;

	envvars = mini->envvars;
	while (envvars)
	{
		if (envvars->print)
		{
			printf("%s", envvars->key);
			printf("=");
			printf("%s\n", envvars->value);
		}
		envvars = envvars->next;
	}
	return (0);
}

int	option_error(char error_char)
{
	printf("env: invalid option -- '%c'\n", error_char);
	return (125);
}

int	arg_error(char *str)
{
	printf("env: '%s': No such file or directory\n", str);
	return (127);
}

int	custom_env(t_minishell *mini)
{
	t_node	*tokenlst;

	tokenlst = mini->commands->tokens;
	if (tokenlst->next)
	{
		tokenlst = tokenlst->next;
		if (tokenlst->token[0] == '-' && !(tokenlst->token[1]))
			return (0);
		else if (tokenlst->token[0] == '-' && tokenlst->token[1])
			return (option_error(tokenlst->token[1]));
		else
			return (arg_error(tokenlst->token));
	}
	else
		return (print_envvars(mini));
}
