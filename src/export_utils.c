/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:31:27 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/12 00:31:27 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*skip_plus(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '+')
		i++;
	if (str[i] != '+')
		return (str);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	j = 0;
	while (str[j])
	{
		if (j == i)
			j++;
		new_str[j - (j > i)] = str[j];
		if (str[j] == '\0')
			break ;
		j++;
	}
	new_str[j - 1] = '\0';
	return (new_str);
}

int	export_no_args(t_minishell *mini)
{
	t_env	*envvars;

	envvars = mini->envvars;
	while (envvars)
	{
		printf("declare -x %s", envvars->key);
		if (envvars->print)
		{
			printf("=");
			printf("\"%s\"", envvars->value);
		}
		printf("\n");
		envvars = envvars->next;
	}
	return (0);
}

t_env	*export_args(char *var)
{
	t_env		*new_env;
	size_t		i;

	i = 0;
	new_env = malloc(sizeof(t_env));
	while (var[i] != '=' && var[i] != '\0')
		i++;
	new_env->key = malloc(i + 1);
	ft_strlcpy(new_env->key, var, i + 1);
	if (var[i] == '=')
	{
		new_env->print = true;
		new_env->value = ft_strdup(var + i + 1);
	}
	else
	{
		new_env->print = false;
		new_env->value = ft_strdup("");
	}
	return (new_env);
}
