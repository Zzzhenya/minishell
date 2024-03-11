#include "../minishell.h"

// go through the envp list - find the variable
	// if the variable name exists in the envp list
		// unset the variable by removing it from linked list
	// if the variable does not exist? - do nothng

int arr_len(char **arr)
{
	int len = 0;

	if (!arr)
		return (len);
	while (arr[len] != NULL)
		len ++;
	return (len);
}

/* TESTTTTT */

void    exec_unset(char **argv, t_envp *my_data)
{
	t_list	*current;
	t_list	*prev;
	char 	**arr;

	current = *(my_data->envlist);
	prev = current;
	while (current != NULL)
	{
		arr = NULL;
      	arr = ft_split((char *)current->content, '=');
		if (!ft_strncmp(arr[0], argv[1], ft_strlen(argv[1])))
		{
			prev->next = current->next;
			ft_lstdelone(current, free_string);
			free_arr(arr, arr_len(arr));
			g_exit_status = 0;
			return;
		}
		free_arr(arr, arr_len(arr));
		prev = current;
		current = current->next;
	}
	g_exit_status = 0;
}