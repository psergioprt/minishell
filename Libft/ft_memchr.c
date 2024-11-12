/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:50:25 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 13:20:17 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: memchr()
The  memchr()  function  scans  the  initial n bytes of the memory area pointed
to by s for the first instance of c. Both c and the bytes of the memory area 
pointed to by s are interpreted as unsigned char.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	uc;

	str = (unsigned char *)s;
	uc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == uc)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
/*
#include <string.h>

int	main(void)
{
	char str[] = "name .user";
	char a = '.';
	char *ret;
	char *sys_ret;

	ret = ft_memchr(str, a, 6);
	sys_ret = memchr(str, a, 6);
	printf("Myfunc: %s\n", ret);
	printf("Sysfunc: %s\n", sys_ret);
	return (0);
}*/
