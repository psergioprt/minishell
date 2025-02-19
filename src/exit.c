/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:58:30 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/23 13:58:30 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	do_exit(t_minishell *mini, int error_code)
{
	mini->exit_status = error_code;
	free_envvars(mini);
	free_commands(mini->commands);
	free_list(mini);
	cleanup_fd(mini);
	exit(error_code);
}

void	calculate_exit(t_minishell *mini, t_node *nodelst)
{
	if (ft_atoll(nodelst->token) < 0)
	{
		printf("exit\n");
		do_exit(mini, (256 + ft_atoll(nodelst->token)));
	}
	else
	{
		printf("exit\n");
		do_exit(mini, (ft_atoll(nodelst->token) % 256));
	}
}

int	get_exit(t_minishell *mini, t_node *nodelst)
{
	nodelst = nodelst->next;
	if (!is_num(nodelst->token) || m_long(nodelst->token))
	{
		printf("exit\n");
		printf("exit: %s: numeric argument required\n", nodelst->token); //TODO trocar para ft_putstr_fd 2
		do_exit(mini, 2);
		return (2);
	}
	else if (nodelst->next)
	{
		printf("exit\n");
		printf("exit: too many arguments\n"); //TODO trocar para ft_putstr_fd 2
		mini->exit_status = 1;
		return (1);
	}
	else
		calculate_exit(mini, nodelst);
	return (0);
}

int	custom_exit(t_minishell *mini)
{
	t_node	*nodelst;

	nodelst = mini->commands->tokens;
	if (!nodelst->next)
	{
		printf("exit\n");
		do_exit(mini, 0);
		return (0);
	}
	else
		return (get_exit(mini, nodelst));
	return (0);
}
