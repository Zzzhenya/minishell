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

int main(int argc, char **argv, char **envp)
{
	t_envp	vars;
	int i = 0;

	printf("%p\n", vars.envlst);
	*(vars.envlst) = NULL;
	while (envp[i] != NULL)
	{
		ft_lstadd_back(vars.envlst, ft_lstnew(ft_strdup(envp[i])));
		i ++;
	}
	print_stack(*(vars.envlst));
	return (0);
}