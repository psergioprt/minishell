/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:58:55 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 12:26:19 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: memcpy()
The  memcpy() function copies n bytes from memory area src to memory area dest.
The memory areas must not overlap.  Use memmove(3) if the memory areas do 
overlap.
memcpy() and memmove() are both standard C-language library functions used to 
copy blocks of memory between different locations. The main difference between 
memcpy() and memmove() is in how they handle overlapping memory regions. When 
copying memory, memcpy assumes that the source and destination memory regions 
do not overlap, and will produce undefined behavior if they do. In contrast, 
memmove() is designed to handle overlapping memory regions and will copy the 
memory correctly regardless of whether the regions overlap or not.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*
#include <string.h>

int	main(void)
{
	char	ptr2[] = "Hello World Hello";
	char	ptr[50];
	char	s_ptr2[] = "Hello World Hello";
	char	s_ptr[50];
	size_t n = 10;

	ft_memcpy(ptr, ptr2, n);
	memcpy(s_ptr, s_ptr2, n);
	printf("Myfunc: %s\n", ptr);
	printf("Sysfunc: %s\n", s_ptr);
	return (0);
}*/
