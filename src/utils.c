/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:33:38 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/09 15:33:38 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_node(t_minishell *mini)
{
	int		i;
	t_node	*temp;

	i = 0;
	temp = mini->tokenlst; // Temporary pointer for counting
	while (temp) {
		i++;
		temp = temp->next;
	}
	return (i);
}

t_env	*find_key(t_minishell *mini, char *key)
{
	t_env	*envvars;

	envvars = mini->envvars;
	printf("Key: %s\n", key); //TODO apagar testes
 	while (envvars)
	{
		if (ft_strcmp(key, envvars->key) == 0)
			return(envvars);
		envvars = envvars->next;
	} 
	return(NULL);
}

int	check_valid_key(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (1);
	if (str[i] == '=' || ft_isdigit(str[i]))
		return (1);
	while (str[i] != '=' && str[i])
	{
		if(!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
