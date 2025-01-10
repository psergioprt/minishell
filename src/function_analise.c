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

void	first_token(t_minishell *mini)
{
	int		ret;
	size_t	len;

	ret = 0;
	len = ft_strlen(mini->tokenlst->token);
	if (!ft_strncmp(mini->tokenlst->token, "echo", len))
		ret = custom_echo(mini);
		// printf("Fazer o echo\n");
	else if (!ft_strncmp(mini->tokenlst->token, "cd", len))
		ret = custom_cd(mini);
		//printf("Fazer o cd\n");
	else if (!ft_strncmp(mini->tokenlst->token, "pwd", len))
		printf("Fazer o pwd\n");
		//ret = execute_execve(mini);
	else if (!ft_strncmp(mini->tokenlst->token, "export", len))
		ret = custom_export(mini);
		//printf("Fazer o export\n");
	else if (!ft_strncmp(mini->tokenlst->token, "unset", len))
		ret = custom_unset(mini);
		//printf("Fazer o unset\n");
	else if (!ft_strncmp(mini->tokenlst->token, "env", len))
		ret = custom_env(mini);	
		//printf("Fazer o env\n");
	else if (!ft_strncmp(mini->tokenlst->token, "exit", len))
		printf("Fazer o exit\n");
	else
		ret = execute_execve(mini);
	if (ret <= 0)
		printf("Error, command not found!\n");
}
