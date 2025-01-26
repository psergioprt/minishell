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
	free_envvars(mini);
	free_list(mini);
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

	nodelst = mini->tokenlst; //exit
	if (!nodelst->next)
	{
		do_exit(mini, 0);
		return (0);
	}
	else
	{
		printf("exit\n");
		get_exit(mini, nodelst);
	}
	printf("nodelst: %s\n", nodelst->token);
	return (0);
}
