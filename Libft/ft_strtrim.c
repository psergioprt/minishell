/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:24:12 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 12:54:05 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: strtrim()
Allocates (with malloc(3)) and returns a new string, which is the result of 
the concatenation of ’s1’ and ’s2’.   
*/

#include "libft.h"

static int	ft_is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		k;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	k = 0;
	while (s1[start] && ft_is_set(s1[start], set))
		start++;
	while (end > start && ft_is_set(s1[end], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	while (start <= end)
		str[k++] = s1[start++];
	str[k] = '\0';
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", ft_strtrim(" pMy name is Lukam ", " m"));
	return (0);
}*/
