/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:58:41 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/08 10:58:41 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int custom_cd(t_minishell *mini)
{
	char *path;
	t_node *node;
	//TODO: tem de ir buscar o path, relative ou absolute
	//TODO: como no subject diz so absolute ou relative path, so fazer esses
	node = mini->tokenlst;
	if (!node->next)
	{
		ft_error("cd: missing argument", mini);
		return (-1);
	}
	node = node->next; //Supostamente estara aqui o path
	if (node->next)
	{
		ft_error("cd: too many arguments", mini);
		return (-1);
	}
	path = node->token;
	if (chdir(path) == -1)
	{
		printf("cd error\n");
		return (-1);
	}
	return (1);
}
