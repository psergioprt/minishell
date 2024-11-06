/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:54:21 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 12:52:33 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: tolower()
This function convert uppercase letters to lowercase.

If  c is an uppercase letter, tolower() returns its lowercase equivalent, 
if a lowercase repre sentation exists in the current locale.  
Otherwise, it returns  c.
If c is neither an unsigned char value nor EOF, the behavior of these functions 
is undefined.
*/

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c = c + 32;
	}
	return (c);
}
/*
#include <ctype.h>

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("Myfunc: %c\n", ft_tolower(argv[1][0]));
		printf("Sysfunc: %c\n", tolower(argv[1][0]));
	}
	return (0);
}*/
