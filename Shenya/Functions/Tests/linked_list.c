#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list *ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->content = content;
	new_node->next = 0;
	return (new_node);
}


t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (lst);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

int ft_lstsize(t_list *lst)
{
	int 	size;
	t_list	*current;

	size = 0;
	current = lst;
	while (current)
	{
		size ++;
		current = current->next;
	}
	return (size);
}

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

void ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

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