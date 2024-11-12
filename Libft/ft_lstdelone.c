/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:51:53 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 14:26:25 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: lstdelone()
Takes as a parameter a node and frees the memory of the node’s content using the
function ’del’ given as a parameter and free the node. The memory of ’next’ must
not be freed.
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	(del)(lst->content);
	free(lst);
	lst = NULL;
}
/*
void del_data(void *content)
{
    free(content);
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

    printf("Antes de limpar:\n");
    t_list *current = myList;
    while (current != NULL)
    {
        printf("%d\n", ((t_data *)(current->content))->value);
        current = current->next;
    }

    if (myList != NULL)
    {
	    t_list *temp = myList;
	    myList = myList->next;
	    ft_lstdelone(temp, del_data);
    }

    printf("\nDepois de limpar:\n");
    current = myList;
    while (current != NULL)
   {
        printf("%d\n", ((t_data *)(current->content))->value);
        current = current->next;
   }
    return 0;
}*/
