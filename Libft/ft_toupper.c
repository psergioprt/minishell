/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:56:36 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 12:47:06 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: toupper()
This function convert lowercase letters to uppercase.
If c is a lowercase letter, toupper() returns its uppercase equivalent, 
if an uppercase representation exists in the current locale.
Otherwise, it returns  c.
If c is neither an unsigned char value nor EOF, the behavior of these functions 
is undefined.
*/

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = c - 32;
	}
	return (c);
}
/*
#include <ctype.h>

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("Myfunc: %c\n", ft_toupper(argv[1][0]));
		printf("Sysfunc: %c\n", toupper(argv[1][0]));
	}
	return (0);
}*/
