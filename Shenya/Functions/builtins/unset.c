#include "../minishell.h"

// go through the envp list - find the variable
	// if the variable name exists in the envp list
		// unset the variable by removing it from linked list
	// if the variable does not exist? - do nothng

/*

unset 1
bash: unset: `1': not a valid identifier
echo $? -> 1

unset haha=hello
bash: unset: `haha=hello': not a valid identifier
echo $? -> 1

unset non-existing-var
echo $? -> 0

unset exiting-var
echo $? -> 0

unset var1 var2  -> unsets both variables
echo $? -> 0



int arr_len(char **arr)
{
	int len = 0;

	if (!arr)
		return (len);
	while (arr[len] != NULL)
		len ++;
	return (len);
}
*/
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
	g_exit_status = 0;
}

/* TESTTTTT */

//void    exec_unset(char *var, t_envp *my_data)
void    exec_unset(char **argv, t_envp *my_data)
{
	int i;

	i = 1;
	while (argv[i] != NULL)
	{
		unset_one_var(argv[i], my_data);
		i ++;
	}
}