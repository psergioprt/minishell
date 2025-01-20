/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:11:31 by pauldos-          #+#    #+#             */
/*   Updated: 2024/11/12 16:36:14 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: lstadd_back()
Adds the node ’new’ at the end of the list.
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newa)
{
	t_list	*temp;

	if (*lst == NULL)
	{
		*lst = newa;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = newa;
}
/*
void    print_list(t_list *lst)
{
        while (lst != NULL)
        {
                printf(" %d ->", *(int *)lst->content);
                lst = lst->next;
        }
        printf(" NULL\n");
}

int     main(void)
{
        t_list *head = NULL;
        int     i = 1;
        int     *data;

        while (i <= 5)
        {
                t_list *new_node = (t_list *)malloc(sizeof(t_list));
                if (new_node == NULL)
                {
                        fprintf(stderr, "Memory allocation failed\n");
                        return (1);
                }
                data = (int *)malloc(sizeof(int));
                if (data == NULL)
                {
                        fprintf(stderr, "Memory allocation failed\n");
                        exit(1);
                }
                *data = i;
                new_node->content = data;
                new_node->next = NULL;
                ft_lstadd_back(&head, new_node);
                ++i;
        }
        printf("Linked List: ");
        print_list(head);
        while (head != NULL)
        {
                t_list *temp = head;
                head = head->next;
                free(temp->content);
                free(temp);
        }
        return (0);
}*/
