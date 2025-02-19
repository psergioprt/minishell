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
	ft_putstr_fd("env: invalid option -- '", 2);
	ft_putchar_fd(error_char, 2);
	ft_putstr_fd("'\n", 2);
	return (125);
}

int	arg_error(char *str)
{
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
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
