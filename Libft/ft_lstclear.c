/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:13:55 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 13:46:55 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: ft_lstclear()
Deletes and frees the given node and every successor of that node, using the 
function ’del’ and free(3). Finally, the pointer to the list must be set to NULL.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = ptr;
	}
	*lst = NULL;
}
/*
typedef struct s_data
{
    int value;
} t_data;

void del_data(void *content)
{
    free(content);
}

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

    ft_lstclear(&myList, del_data);

    printf("\nDepois de limpar:\n");
    current = myList;
    while (current != NULL)
    {
        printf("%d\n", ((t_data *)(current->content))->value);
        current = current->next;
    }
    return 0;
}*/
