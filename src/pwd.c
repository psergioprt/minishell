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
		printf("CWD error\n");
		return (1);
	}
	printf("%s\n", directory);
	return (0);
}

int custom_pwd(t_minishell *mini)
{
	t_node  *nodes;

	nodes = mini->commands->tokens; //mudei de mini->tokenlst;
	if (nodes->next != NULL)
	{
		nodes = nodes->next;//flag ou pipe
		if (nodes->token[0] == '-' && nodes->token[1])//tinha feito  && !(nodes->token[1] == 'L' || nodes->token[1] == 'P'), mas diz "no options" no subject entao assumo que nao deva ter
		{
			printf("pwd: %s: invalid option\n", nodes->token);
			return (2);
		}
/* 		else if (nodes->token[0] == '|')
			printf("FAZ A MERDA DOS PIPES\n"); */ //TODO: isto e necessario?
		else
			return (pwd_execute());
	}
	return (pwd_execute());
} 
