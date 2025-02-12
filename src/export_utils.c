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
	new_str = malloc(ft_strlen(str));
	if (!new_str)
		return (NULL);
	j = 0;
	while (str[j])
	{
		if (j == i)
			j++;
		new_str[j - (j > i)] = str[j];
		j++;
	}
	new_str[j - 1] = '\0';
	return (new_str);
}
