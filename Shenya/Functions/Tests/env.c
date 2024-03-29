#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_envp
{
	//char	**env;
	t_list	**envlst; // 8
	char 	**envarr; // 8
	char	*cd_hist; // 12
	int		count; // 4
}	t_envp;


size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len ++;
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i] != '\0')
			i ++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i ++;
	}
	if (i < size)
		dest [i] = '\0';
	while (src[i] != '\0')
		i ++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, ft_strlen(s) + 1);
	return (ptr);
}
/*
int get_len(char **envp)
{
	int i = 0;

	while (envp[i] != NULL)
	{
		i ++;
	}
	return (i);
}

void free_prev(char **env, int len)
{
	int i = 0;

	while (i < len)
	{
		free(env[i]);
		env[i] = NULL;
		i ++;
	}
	free(env);
	env = NULL;
}

int store_envp(t_envp *vars, char **envp)
{
	int len;
	int i = 0;
	
	len = get_len(envp);
	vars->env = malloc(sizeof(char *) * len + 1);
	if (!vars->env)
		return (-1);
	vars->env[len] = NULL;
	while (i < len)
	{
		vars->env[i] = ft_strdup(envp[i]);
		if (!vars->env[i])
		{
			free_prev(vars->env, i);
			return (-1);
		}
		i ++;
	}
	vars->count = len;
	return (0);
}
*/

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

void	print_stack(t_list *stack)
{
	t_list	*current;
	int i = 0;

	current = stack;
	printf("List data\n");
	while (current != NULL)
	{
		printf("    %d: %s\n", i, (char *)current->content);
		i ++;
		current = current->next;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*current;

	printf("Cleaning list\n");
	while (*lst)
	{
		free ((*lst)->content);
		(*lst)->content = NULL;
		current = *lst;
		*lst = current->next;
		free(current);
	}
	*lst = 0;
}

int main(int argc, char **argv, char **envp)
{
	int i = 0;
	t_list *lst;
	char *temp;
	t_list *node;

	temp = NULL;
	lst = NULL;
	while (envp[i] != NULL)
	{
		temp = ft_strdup(envp[i]);
		ft_lstadd_back(&lst, ft_lstnew(temp));
		temp = NULL;
		printf("%s\n", envp[i]);
		i ++;
	}
	while (lst)
	{
		node = lst;
		lst = node->next;
		printf("%s\n", (char *)(node)->content);
		free ((char *)node->content);
		node->content = NULL;
		free (node);
		node = NULL;
	}
	lst = NULL;
	temp = NULL;
	free (node);
	node = NULL;
	/*print_stack(*(vars.envlst));
	ft_lstclear(vars.envlst);
	print_stack(*(vars.envlst));*/
	printf("%d\n", argc);
	(void)argv;
	return (0);
}