#include "../include/minishell.h"

/* 
	Clear the content of the envlist node
*/

void	free_string(void *input)
{
	char	*str;

	str = (char *)input;
	free (str);
	str = NULL;
}

/*
	Clear entire envlist
*/

void	clear_envlist(t_envp *env)
{
	ft_lstclear(&env->envlist, free_string);
}

/*
	Store env variables in a linked list pointed by env->envlist
	Store number of of variables in env->count 
*/

int	store_envp(t_envp *env, char **envs)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (envs[i] != NULL)
	{
		temp = ft_strdup(envs[i]);
		if (!temp)
		{
			clear_envlist(env);
			return (-1);
		}
		ft_lstadd_back(&env->envlist, ft_lstnew(temp));
		temp = NULL;
		env->count ++;
		i ++;
	}
	return (0);
}

/*
	extract env variables from the linked list and store in envarr array
*/

int	extract_envarr(t_envp *env)
{
	t_list	*current;
	int		i;
	int		len;

	i = 0;
	len = 0;
	current = NULL;
	current = env->envlist;
	len = ft_lstsize(current);
	env->envarr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env->envarr)
		return (-1);
	env->envarr[len] = NULL;
	while (current != NULL)
	{
		env->envarr[i] = ft_strdup((char *)current->content);
		if (!env->envarr[i])
		{
			free_arr(env->envarr, i);
			clear_envlist(env);
			return (-1);
		}
		current = current->next;
		i ++;
	}
	return (0);
}