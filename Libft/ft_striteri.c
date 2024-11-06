/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:08:02 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 15:44:54 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: striteri()
Applies the function ’f’ on each character of the string passed as argument, 
passing its index as first argument. Each character is passed by address to ’f’ 
to be modified if necessary.
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
/*
void	myfunc(unsigned int i, char *c)
{
	printf("[%d] * %c\n", i, *c);
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 'a' + 'A';
}

int	main(void)
{
	char str[] = "My name is Luka 123";
	printf("Original string: %s\n", str);
	ft_striteri(str, myfunc);
	printf("Striteri string: %s\n", str);
	return (0);

}
*/
//or (*f)(i, &s[i]);
