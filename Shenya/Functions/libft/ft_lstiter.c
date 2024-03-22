/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:49:29 by sde-silv          #+#    #+#             */
/*   Updated: 2023/10/04 13:57:04 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void    ft_multiplier(void  *content)
{
    *(int *)content = *(int *)content * 1000;
}
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(f)(lst->content);
		lst = lst->next;
	}
}
/*
int main(void)
{
	t_list *head;
	t_list *current;
	t_list **lst;
	t_list	*last;
	int   size;

    int     *one;
    int     *two;
    int     *three;
    int     *four;

    one = (int  *)malloc(sizeof(int) * 1);
    two = (int  *)malloc(sizeof(int) * 1);
    three = (int  *)malloc(sizeof(int) * 1);
    four = (int  *)malloc(sizeof(int) * 1);

    *one = 20;
    *two = 30;
    *three = 10;
    *four = 40;

	head = ft_lstnew((void *)one);
    *lst = head;
    head->next = ft_lstnew((void *)two);
	ft_lstadd_front(lst, ft_lstnew((void *)three));
	ft_lstadd_back(lst, ft_lstnew((void *)four));

    current = *lst;
    
    size = ft_lstsize(*lst);
    printf("size: %d\n", size);
    while (current != NULL)
    {
    	printf("%zu\n", *(size_t *)(current->content));
        current = current->next;
    }
    last = ft_lstlast(*lst);
    printf("last: %zu\n", *(size_t *)(last->content));
    
    
    ft_lstiter(*lst, ft_multiplier);
    current = *lst;
    while (current != NULL)
    {
    	printf("%zu\n", *(size_t *)current->content);
        current = current->next;
    }

	return (0);
}
*/
