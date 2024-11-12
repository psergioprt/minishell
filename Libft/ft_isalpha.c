/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:56:37 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 11:52:59 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: isalpha()
checks  for  an  alphabetic  character;  in the standard "C" locale, it is 
equivalent to (isupper(c) || islower(c)).  In some locales, there may  be  
additional  characters  for which isalpha() is true—letters which are neither 
uppercase nor lowercase.
*/

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/*
#include <ctype.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf ("Myfunc %d\n", ft_isalpha(argv[1][0]));
		printf ("Sysfunc %d\n", isalpha(argv[1][0]));
	}
	return (0);
}*/
