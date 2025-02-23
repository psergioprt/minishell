/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:29:21 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/26 16:29:21 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit((unsigned char)*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

static bool	check_valid_nbr(char *str)
{
	long	signal;
	long	n;
	int		i;

	i = 0;
	if (!ft_strcmp("-9223372036854775808", str))
		return (true);
	signal = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		signal = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	n = 0;
	while (ft_isdigit(str[i]))
	{
		if (n > n * 10 + (str[i] - '0'))
			return (false);
		n = n * 10 + (str[i] - '0');
		i++;
	}
	n = n * signal;
	return (true);
}

bool	m_long(char *str)
{
	if (check_valid_nbr(str))
		return (false);
	else
		return (true);
}

int	is_num(char *str)
{
	if (!str || !*str)
		return (0);
	else
	{
		if (*str == '-' && *(str + 1) == '-' && !*(str + 2))
			return (1);
		else if ((*str == '-' || *str == '+') && !*(str + 1))
			return (0);
		else if (*str == '-' || *str == '+')
			str++;
		while (*str)
		{
			if (!(*str >= '0' && *str <= '9')
				&& *str != ' ' && !(*str >= 9 && *str <= 13))
				return (0);
			str++;
		}
	}
	return (1);
}
