/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 09:10:50 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 13:20:39 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: lstsize()
Counts the number of nodes in a list.
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*new_node;
	int		size;

	new_node = lst;
	size = 0;
	if (lst == NULL)
		return (0);
	while (new_node != NULL)
	{
		size++;
		new_node = new_node->next;
	}
	return (size);
}
/*
int	main(void)
{
	t_list *head = NULL;
	int	i = 5;
	int	*data;

	while (i >= 2)
	{
		t_list *new_node = (t_list *)malloc(sizeof(t_list));
		data = (int *)malloc(sizeof(int));
		*data = i;	
		new_node->content = data;
		new_node->next = NULL;
		ft_lstadd_front(&head, new_node);
		--i;
	}
	printf("%d", ft_lstsize(head));
	return (0);
}*/
