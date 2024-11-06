/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:48 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 11:54:02 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: isascii()
checks whether c is a 7-bit unsigned char value that fits into the ASCII 
character set.
*/

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
#include <ctype.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("Myfunc: %d\n", ft_isascii(argv[1][0]));
		printf("Sysfunc: %d\n", isascii(argv[1][0]));
	}
	return (0);
}*/
