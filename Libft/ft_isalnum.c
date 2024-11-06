/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:39:51 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 11:55:13 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: isalnum()
checks for an alphanumeric character; it is equivalent to 
(isalpha(c) || isdigit(c)).
*/

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/*#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("Myfunc %d\n", ft_isalnum(argv[1][0]));
		printf("Sysfunc %d\n", ft_isalnum(argv[1][0]));
	}
	return (0);
}*/
