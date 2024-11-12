/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:30:02 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 13:29:16 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
DESCRIPTION: strnstr()
The strnstr() function locates the first occurrence of the null-terminated string
little in the string big, where not more than len characters are searched.  
Characters that appear after a ‘\0’ character are not searched. 
Since the strnstr() function is a FreeBSD specific API, it should only be used 
when portability is not a concern.
If little is an empty string, big is returned; if little occurs nowhere in big, 
NULL is returned; otherwise a pointer to the first character of the first 
occurrence of little is returned.
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	h;

	if (!big && !len)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (*big && len--)
	{
		h = 0;
		while (*(big + h) == *(little + h)
			&& *(little + h) && h <= len)
		{
			if (!*(little + h + 1))
				return ((char *)big);
			h++;
		}
		big++;
	}
	return (NULL);
}
/*
#include <string.h>

int	main(void)
{
	char 	str[] = "My name is Luka";
	char 	str2[] = "is";
	char 	*myfunc = ft_strnstr(str, str2, 10);

	printf("Myfunc: %s\n", myfunc);
	return (0);
}*/
