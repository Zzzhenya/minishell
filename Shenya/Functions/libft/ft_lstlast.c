/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:51:29 by sde-silv          #+#    #+#             */
/*   Updated: 2023/10/04 13:51:38 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (lst);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}
/*
int main(void)
{
	t_list *head;
	t_list *current;
	t_list **lst;
	t_list	*new;
	int size;

	head = 0;
	head = ft_lstnew((void *)10);
	//head->next = ft_lstnew((void *)20);
	//new = ft_lstnew((void *)30);
	*lst = head;
	//new = ft_lstnew((void *)30);
	//ft_lstadd_front(lst, new);
    current = *lst;
    size = ft_lstsize(*lst);
    printf("size: %d\n", size);
    while (size > 0)
    {
    	printf("%zu\n", (size_t)current->content);
        current = current->next;
        size --;
    }
    printf("last: %zu\n", (size_t)(ft_lstlast(*lst))->content);
	return (0);
}
*/
