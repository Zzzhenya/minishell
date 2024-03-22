#include "fork.h"

void unset_one_var(char *var, t_envp *my_data)
{
	t_list	*current;
	t_list	*prev;
	char 	**arr;

	current = (my_data->envlist);
	prev = current;
	while (current != NULL)
	{
		arr = NULL;
      	arr = ft_split((char *)current->content, '=');
		if (!ft_strncmp(arr[0], var, ft_strlen(var)))
		{
			prev->next = current->next;
			ft_lstdelone(current, free_string);
			free_arr(arr, get_arg_count(arr));
			g_exit_status = 0;
			return;
		}
		free_arr(arr, get_arg_count(arr));
		prev = current;
		current = current->next;
	}
}

/* TESTTTTT */

void    exec_unset(char **argv, t_envp *my_data)
{
	int i;

	i = 1;
	g_exit_status = 0;
	while (argv[i] != NULL)
	{
		unset_one_var(argv[i], my_data);
		i ++;
	}
}