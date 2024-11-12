/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:39:56 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 15:21:12 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION: lstiter()
Iterates the list ’lst’ and applies the function ’f’ on the content of each node.
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == 0 || f == 0)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void double_data(void *content)
{
    int *value = (int *)content;
    *value = (*value) * 2;
}

void print_data(void *content)
{
	printf("%d\n", *((int *)content));
}

typedef struct s_data
{
	int value;
} t_data;

int main()
{
    t_list *myList = NULL;

    t_data *data1 = malloc(sizeof(t_data));
    data1->value = 42;

    t_data *data2 = malloc(sizeof(t_data));
    data2->value = 84;

    ft_lstadd_back(&myList, ft_lstnew(data1));
    ft_lstadd_back(&myList, ft_lstnew(data2));

    printf("Before applying ft_lstiter:\n");
    ft_lstiter(myList, print_data);

    ft_lstiter(myList, double_data);

    printf("\nAfter applying ft_lstiter:\n");
    ft_lstiter(myList, print_data);

    ft_lstclear(&myList, free);

    return 0;
}*/
