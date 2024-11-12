/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:27:34 by pauldos-          #+#    #+#             */
/*   Updated: 2023/10/31 13:05:59 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: strrchr()
The strrchr() function returns a pointer to the last occurrence of the character
c in the string s.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			p = ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		p = ((char *)&s[i]);
	return (p);
}
/*
int	main(void)
{
	char	str[] = "My name is Luka";
	char	a = 'i';
	char	*b = ft_strrchr(str, a);

	printf("After the last '%c' we get '%s'", a, b);
	return (0);
}*/
