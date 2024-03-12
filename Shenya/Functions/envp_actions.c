#include "minishell.h"

//frees the heap envp array from the given position
void free_arr(char **env, int len)
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

/*


 counts the number of items in envp array 
static int get_len(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i ++;
	return (i);
}

 Copies the envp array from static memory to heap 
int store_envp(t_envp *vars, char **envp)
{
	int len;
	int i;

	i = 0;
	len = get_len(envp);
	vars->envp = malloc(sizeof(char *) * len + 1);
	if (!vars->envp)
		return (-1);
	vars->envp[len] = NULL;
	while (i < len)
	{
		vars->envp[i] = ft_strdup(envp[i]);
		if (!vars->envp[i])
		{
			free_arr(vars->envp, i);
			return (-1);
		}
		i ++;
	}
	vars->count = len;
	return (0);
}*/

void free_string(void	*input)
{
	char *str;

	str = (char *)input;
	free (str);
	str = NULL;
}

void clear_envlist(t_envp *my_data)
{
	ft_lstclear(&my_data->envlist, free_string);
}

int store_envp(t_envp *vars, char **envp)
{
	int 	i;
	char *temp;

	i = 0;
	temp = NULL;
	while (envp[i] != NULL)
	{
		temp = ft_strdup(envp[i]);
		if (!temp)
		{
			//free_list(vars->envlist);
			return (-1);
		}
		ft_lstadd_back(&vars->envlist, ft_lstnew(temp));
		temp = NULL;
		i ++;
	}
	return (0);
}



int extract_envarr(t_envp *my_data)
{
	t_list	*current;
	int i = 0;

	int len = 0;

	current = (my_data->envlist);
	len = ft_lstsize(current);
	//current = *(my_data->envlist);
	my_data->envarr = malloc(sizeof(char *) * len + 1);
	if (!my_data->envarr)
		return (-1);
	my_data->envarr[len] = NULL;
	while (current != NULL)
	{
		my_data->envarr[i] = ft_strdup((char *)current->content);
		if (!my_data->envarr[i])
		{
			//free_arr(vars->envp, i);
			return (-1);
		}
		current = current->next;
		i ++;
	}
	my_data->count = i;
	return (0);
}



