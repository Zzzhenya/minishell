/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:51:53 by sde-silv          #+#    #+#             */
/*   Updated: 2023/10/04 13:52:04 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst == 0)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != 0)
			temp = temp->next;
		temp->next = new;
	}
}
/*
int main(void)
{
	t_list *head;
	t_list *current;
	t_list **lst;
	int   size;

	head = ft_lstnew((void *)20);
	head->next = ft_lstnew((void *)30);
	*lst = head;
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
    printf("last: %zu\n", (size_t)(ft_lstlast(*lst))->content);
	return (0);
}
*/
