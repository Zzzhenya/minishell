/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:04:02 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/02 19:15:32 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_status_print(char *str)
{
	g_exit_status = 1;
	print_export_error(str, NULL, " : not a valid identifier");
}

void	export_one_var(char *str, char *var, t_envp *my_data)
{
	char	*line;

	line = NULL;
	line = ft_strdup(str);
	unset_one_var(var, my_data);
	ft_lstadd_back(&my_data->envlist, ft_lstnew(line));
	my_data->count++;
}

void	multi_export(char **argv, t_envp *my_data, int count, int i)
{
	char	*str;
	char	**arr;

	str = NULL;
	arr = NULL;
	while (i < count)
	{
		printf("str %s\n", argv[i]);
		str = ft_strchr(argv[i], '=');
		if (str && argv[i][0] != '=')
		{
			arr = split_at_first_occ(argv[i], '=', 0);
			if (!is_valid_var_start(arr[0][0]) || !is_valid_var_char(arr[0]))
				set_status_print(arr[0]);
			else
				export_one_var(argv[i], arr[0], my_data);
			free_arr(arr, get_arg_count(arr));
		}
		else
		{
			if (!is_valid_var_start(argv[i][0]) || !is_valid_var_char(argv[i]))
				set_status_print(argv[i]);
		}
		i ++;
	}
}

void	exec_export(char **argv, t_envp *my_data)
{
	int		count;
	char	**arr;

	count = 0;
	arr = NULL;
	count = count_non_empty_strings(&argv[1]);
	arr = strip_empty_strings(&argv[1]);
	g_exit_status = 0;
	if (count == 0)
		print_variables_list(my_data->envarr);
	else
		multi_export(arr, my_data, count, 0);
	if (arr)
		free_arr(arr, count);
}
