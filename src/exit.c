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
	g_exit_code = error_code;
	free_envvars(mini);
	free_commands(mini->commands);
	free_list(mini);
	cleanup_fd(mini);
	exit(error_code);
}

void	calculate_exit(t_minishell *mini, t_node *nodelst)
{
	if (ft_strcmp(nodelst->token, "--") == 0)
	{
		printf("exit\n");
		do_exit(mini, mini->exit_status);
	}
	else if (ft_atoll(nodelst->token) < 0)
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
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(nodelst->token, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		do_exit(mini, 2);
		return (2);
	}
	else if (nodelst->next)
	{
		printf("exit\n");
		ft_putstr_fd("exit: too many arguments\n", 2);
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
		do_exit(mini, mini->exit_status);
		return (mini->exit_status);
	}
	else
		return (get_exit(mini, nodelst));
	return (0);
}
