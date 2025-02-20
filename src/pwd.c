/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:01:35 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/15 16:01:35 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd_execute(void)
{
	char	cwd[1024];
	char	*directory;

	directory = getcwd(cwd, sizeof(cwd));
	if (!directory)
	{
		ft_putstr_fd("pwd error\n", 2);
		return (1);
	}
	printf("%s\n", directory);
	return (0);
}

int	custom_pwd(t_minishell *mini)
{
	t_node	*nodes;

	nodes = mini->commands->tokens;
	if (nodes->next != NULL)
	{
		nodes = nodes->next;
		if (nodes->token[0] == '-' && nodes->token[1])
		{
			ft_putstr_fd("pwd: ", 2);
			ft_putstr_fd(nodes->token, 2);
			ft_putstr_fd(": invalid option\n", 2);
			return (2);
		}
		else
			return (pwd_execute());
	}
	return (pwd_execute());
}
