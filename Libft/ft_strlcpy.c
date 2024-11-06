/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:34:28 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 12:37:29 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: strlcpy()
The strlcpy() and strlcat() functions copy and concatenate strings respectively.
They are designed to be safer, more consistent, and less error prone replacements
for strncpy(3) and strncat(3). Unlike those functions, strlcpy() and strlcat() 
take the full size of the buffer (not just the length) and guarantee to 
NUL-terminate the result (as long as size is larger than 0 or, in the case of 
strlcat(), as long as there is at least one byte free in dst).  Note that a byte
for the NUL should be included in size.  Also note that strlcpy() and strlcat() 
only operate on true “C” strings. This means that for strlcpy() src must be 
NUL-terminated and for strlcat() both src and dst must be NUL-terminated.

The strlcpy() function copies up to size - 1 characters from the NUL-terminated 
string src to dst, NUL-terminating the result.
The strlcat() function appends the NUL-terminated string src to the end of dst.
It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the result.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

/*
int	main(void)
{
	size_t	i = 7;
	char	src[] = "Hello World";
	char	dest[50];

	int a = ft_strlcpy(dest, src, i);
	printf("Myfunc: string: %s size: %d\n", dest, a);
	return (0);
}*/
