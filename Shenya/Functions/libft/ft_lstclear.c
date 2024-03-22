/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:53:52 by sde-silv          #+#    #+#             */
/*   Updated: 2023/10/04 13:57:25 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	del(void *ptr)
{
	if (ptr)
	{
        ptr = 0;
	}
}
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	while (*lst)
	{
		(del)((*lst)->content);
		temp = *lst;
		*lst = temp->next;
		free (temp);
	}
	*lst = 0;
}
/*
int main(void)
{
	t_list *head;
	t_list *current;
	t_list **lst;
	t_list	*last;
	int   size;


	head = ft_lstnew((void *)20);
    *lst = head;
    head->next = ft_lstnew((void *)30);
	ft_lstadd_front(lst, ft_lstnew((void *)10));
	ft_lstadd_back(lst, ft_lstnew((void *)40));

    current = *lst;
    
    size = ft_lstsize(*lst);
    printf("size: %d\n", size);
    while (current != NULL)
    {
    	printf("%zu\n", (size_t)current->content);
        current = current->next;
    }
    last = ft_lstlast(*lst);
    printf("last: %zu\n", (size_t)(last->content));
    
    current = *lst;
    ft_lstclear(&head, del);
    printf("Current: %zu\n", (size_t)(current)->content);
    current = current->next;
    printf("Current: %zu\n", (size_t)(current)->content);
	return (0);
}
*/
