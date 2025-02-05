/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:43:02 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/05 15:38:28 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: strdup()
The  strdup() function returns a pointer to a new string which is a duplicate 
of the string s.  Memory for the new string  is  obtained  with malloc(3), 
and can be freed with free(3).
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dst;

	i = 0;
	if (s == NULL)
		return (NULL);
	dst = (char *)malloc(ft_strlen(s) * sizeof (char) + 1);
	if (dst == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
/*
#include <string.h>

int	main(void)
{
	char	s[] = "My name is Luka";

	printf("Myfunc: %s\n", ft_strdup(s));
	printf("Sysfunc: %s\n", strdup(s));
	return (0);
}*/
