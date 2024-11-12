/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:17:38 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 12:59:20 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: strmapi()
Applies the function ’f’ to each character of the string ’s’, and passing its
index as first argument to create a new string (with malloc(3)) resulting
from successive applications of ’f’.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	lower_to_upper(unsigned int i, char str)
{
	printf("i[%d] = %c\n", i, str);
	if (str >= 'a' && str <= 'z')
		return (str - 'a' + 'A');
	return (str);
}

int main()
{
 	char str[10] = "he12lo.";
 	printf("Before strmapi: %s\n", str);
 	char *result = ft_strmapi(str, lower_to_upper);
 	printf("After strmapi: %s\n", result);
	free(result);
 	return 0;
}*/
