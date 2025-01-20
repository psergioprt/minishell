/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:38:05 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/08 22:38:05 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO: falar paulo env with no options or arguments, so ignora se tem algo a frente?

void	print_env()

int custom_env(t_minishell *mini)
{
	t_env	*envvars;

	envvars = mini->envvars;
	while (envvars)
	{
		if (envvars->print)
		{
			printf("%s", envvars->key);
			printf("=");
			printf("%s\n", envvars->value);
		}
		envvars = envvars->next;
	}
	return (1);
}
