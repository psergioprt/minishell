/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:55:37 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/03 15:04:08 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: lstmap()
Iterates the list ’lst’ and applies the function ’f’ on the content of each node.
Creates a new list resulting of the successive applications of the function ’f’.
The ’del’ function is used to delete the content of a node if needed.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;
	void	*set;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		set = f(lst->content);
		new_elem = ft_lstnew(set);
		if (!new_elem)
		{
			del(set);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_elem);
		lst = lst->next;
	}
	return (new_lst);
}
/*
void *square_data(void *content)
{
    int *value = (int *)content;
    int *result = malloc(sizeof(int));
    if (result)
        *result = (*value) * (*value);
    return result;
}

void print_data(void *content)
{
    printf("%d\n", *((int *)content));
}

void free_data(void *content)
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
    data1->value = 4;

    t_data *data2 = malloc(sizeof(t_data));
    data2->value = 7;

    ft_lstadd_back(&myList, ft_lstnew(data1));
    ft_lstadd_back(&myList, ft_lstnew(data2));

    printf("Before applying ft_lstmap:\n");
    ft_lstiter(myList, print_data);

    // Apply the square_data function with ft_lstmap
    t_list *mappedList = ft_lstmap(myList, square_data, free_data);

    printf("\nAfter applying ft_lstmap:\n");
    ft_lstiter(mappedList, print_data);

    // Free the original and mapped lists
    ft_lstclear(&myList, free_data);
    ft_lstclear(&mappedList, free_data);

    return 0;
}*/
