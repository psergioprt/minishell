/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:44:25 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 11:57:53 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: isprint()
checks for any printable character including space.
*/

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <ctype.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
	printf("Myfunc: %d\n", ft_isprint(argv[1][0]));
	printf("Sysfunc: %d\n", isprint(argv[1][0]));
	}
	return (0);
}*/
