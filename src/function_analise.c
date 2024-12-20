/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_analise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:59 by marvin            #+#    #+#             */
/*   Updated: 2024/11/20 16:33:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	first_token(t_minishell *data)
{
	int		ret;
	size_t	len;

	ret = 0;
	len = ft_strlen(data->tokenlst->token);
	if (!ft_strncmp(data->tokenlst->token, "echo", len))
		custom_echo(data);
		// printf("Fazer o echo\n");
	else if (!ft_strncmp(data->tokenlst->token, "cd", len))
		printf("Fazer o cd\n");
	else if (!ft_strncmp(data->tokenlst->token, "pwd", len))
		printf("Fazer o pwd\n");
	else if (!ft_strncmp(data->tokenlst->token, "export", len))
		printf("Fazer o export\n");
	else if (!ft_strncmp(data->tokenlst->token, "unset", len))
		printf("Fazer o unset\n");
	else if (!ft_strncmp(data->tokenlst->token, "env", len))
		printf("Fazer o env\n");
	else if (!ft_strncmp(data->tokenlst->token, "exit", len))
		printf("Fazer o exit\n");
	else
		ret = execute_execve(data);
	if (ret <= 0)
		printf("Error, command not found!\n");
}
