/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:03:17 by pauldos-         #+#    #+#             */
/*   Updated: 2023/10/31 12:42:26 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: strlcat()
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(dst);
	j = 0;
	if (size <= i)
		return (size + ft_strlen(src));
	while (src[j] && i + j < (size - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (ft_strlen(src) + i);
}
/*
int	main (void)
{
	char	str1[] = "My name is Luka ";
	char	str2[] = "And i am a musitian";
	unsigned int	size = 40;
	int	a = myft_strlcat(str1, str2, size);

	printf("%s * %d\n", str1, a);
	return (0);
}*/
