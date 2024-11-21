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

void	first_token(t_node *data)
{
	int		ret;
	size_t	len;

	ret = 0;
	len = ft_strlen(data->token);
	if (!ft_strncmp(data->token, "echo", len))
		printf("Fazer o echo\n");
	else if (!ft_strncmp(data->token, "cd", len))
		printf("Fazer o cd\n");
	else if (!ft_strncmp(data->token, "pwd", len))
		printf("Fazer o pwd\n");
	else if (!ft_strncmp(data->token, "export", len))
		printf("Fazer o export\n");
	else if (!ft_strncmp(data->token, "unset", len))
		printf("Fazer o unset\n");
	else if (!ft_strncmp(data->token, "env", len))
		printf("Fazer o env\n");
	else if (!ft_strncmp(data->token, "exit", len))
		printf("Fazer o exit\n");
	else
		ret = printf("Fazer o execve\n");
	if (ret <= 0)
		printf("Error, command not found!\n");
}
