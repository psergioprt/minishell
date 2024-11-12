/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:30:50 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 12:32:30 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: memmove()
The memmove() function copies n bytes from memory area src to memory area dest.
The memory areas may overlap: copying takes place as though the bytes in src are
first copied into a  temporary  array that does not overlap src or dest, and the
bytes are then copied from the temporary array to dest.
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)src;
	d = (char *)dest;
	if (!dest && !src)
		return (0);
	i = 0;
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <string.h>

int	main(void)
{
	size_t n = 7;

	char src[] = "Hello World";
	char dest[50];
	char src2[] = "Hello World";
	char dest2[50];

	ft_memmove(dest, src, n);
	memmove(dest2, src2, n);
	printf("Myfunc: %s\n", dest);
	printf("Sysfunc: %s\n", dest2);
	return (0);
}*/
