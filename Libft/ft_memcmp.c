/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 07:54:57 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 12:35:20 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: memcmp()
The  memcmp()  function  compares  the first n bytes (each interpreted as 
unsigned char) of the memory areas s1 and s2.
The memcmp() function returns an integer less than, equal to, or greater than 
zero if the first n bytes of s1 is found, respectively, to be less than, 
to match, or be greater than the first n bytes of s2.
For a nonzero return value, the sign is determined by the sign of the  difference
between  the first pair of bytes (interpreted as unsigned char) that differ in 
s1 and s2.
If n is zero, the return value is zero.
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/*
#include <string.h>

int	main(void)
{
	char s1[] = "My name is Luka";
	char s2[] = "My Name is Luka";
	int	myfunc = ft_memcmp(s1, s2, 5);
	int	sysfunc = memcmp(s1, s2, 5);

	printf("Myfunc: %d\n", myfunc);
	printf("Sysfunc: %d\n", sysfunc);
	return (0);
}*/
