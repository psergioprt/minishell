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
	printf("exit\n");	
	exit(error_code);
}

void	get_exit(t_minishell *mini, t_node  *nodelst)
{
	nodelst = nodelst->next;

	if (!is_num(nodelst->token) || m_long(nodelst->token))
	{
		printf("exit: %s: numeric argument required\n", nodelst->token);
		do_exit(mini, 2);
	}
	else if (nodelst->next)
	{
		printf("exit: too many arguments\n");
		mini->exit_status = 1;
	}
	else
	{
		if (ft_atoll(nodelst->token) < 0)
			do_exit(mini, (256 + ft_atoll(nodelst->token)));
		else
			do_exit(mini, (ft_atoll(nodelst->token) % 256));
	}
}

//o maximo que aceita sao 18 numeros 9
int custom_exit(t_minishell *mini)
{
	t_node  *nodelst;

	nodelst = mini->commands->tokens; //mudei de mini->tokenlst;
	if (!nodelst->next)
	{
		do_exit(mini, 0);
		return (0);
	}
	else
		get_exit(mini, nodelst);
	return (0);
}
