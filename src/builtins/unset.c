/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:01:15 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/03 15:25:08 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
void	unset_one_var(char *var, t_envp *my_data)
{
	t_list	*current;
	t_list	*prev;
	char	**arr;
	//char *str = NULL;

	current = (my_data->envlist);
	prev = current;
	while (current != NULL)
	{
		arr = NULL;
		arr = split_at_first_occ((char *)current->content, '=');
		//arr = ft_split((char *)current->content, '=');
		if (!ft_strncmp(arr[0], var, ft_strlen(arr[0]))
			&& !ft_strncmp(arr[0], var, ft_strlen(var)))
		{
			prev->next = current->next;
			ft_lstdelone(current, free_string);
			my_data->count --;
			free_arr(arr, get_arg_count(arr));
			g_exit_status = 0;
			break ;
			//return ;
		}
		free_arr(arr, get_arg_count(arr));
		prev = current;
		current = current->next;
	}
}

/* TESTTTTT */

void	exec_unset(char **argv, t_envp *my_data)
{
	int	i;

	i = 1;
	g_exit_status = 0;
	while (argv[i] != NULL)
	{
		unset_one_var(argv[i], my_data);
		i ++;
	}
}
