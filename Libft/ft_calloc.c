/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 09:24:30 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 12:42:53 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: calloc()
The  calloc()  function allocates memory for an array of nmemb elements
of size bytes each and returns a pointer to the allocated memory. The
memory  is  set  to zero.  If nmemb or size is 0, then calloc() returns
either NULL, or a unique pointer value that can later  be  successfully
passed to free().  If the multiplication of nmemb and size would result
in integer overflow, then calloc() returns an error.  By  contrast,  an
integer  overflow  would  not be detected in the following call to 
malloc(), with the result that an incorrectly sized block of memory  would
be allocated:
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*#include <stdio.h>

int	main(void)
{
	int	i;
	int	n;
	int	*a;
	int	*b;

	i = 0;
	n = 5;
	a = (int *)ft_calloc(n, sizeof(int));
	b = (int *)calloc(n, sizeof(int));
	while (i < n)
	{
		printf("My: %d\t", a[i]);
		printf("Sys: %d\t\n", b[i]);
		i++;
	}
	free (a);
	return (0);
}*/
