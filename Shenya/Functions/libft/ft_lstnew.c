/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:51:05 by sde-silv          #+#    #+#             */
/*   Updated: 2023/10/04 13:51:21 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->content = content;
	new_node->next = 0;
	return (new_node);
}
/*
int main(void)
{
	t_list *head;
	t_list *current;

	head = ft_lstnew((void *)10);
	head->next = ft_lstnew((void *)20);

    current = head;
    while (current != NULL)
    {
    	printf("%zu\n", (size_t)current->content);
        current = current->next;
    }
	return (0);
}
*/
