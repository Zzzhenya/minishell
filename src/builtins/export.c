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

/*
      export varname=varval
      export varname="varval"
      export varname=""
      export varname=
      export 0="ONE"
      bash: export: `0=ONE': not a valid identifier 
      echo $?  -> 1
*/
/*
char	*remove_one_quote_set(char *str)
{
	size_t	end;

	end = 0;
	end = ft_strlen(str) - 1;
	if (str[0] == '\'' && str[end] == '\'')
		str = ft_strtrim(str, "\'");
	else if (str[0] == '\"' && str[end] == '\"')
		str = ft_strtrim(str, "\"");
	return (str);
}*/

void	export_one_var(char **arr, t_envp *my_data)
{
	char	*var;
	char	*val;
	char	*str;

	var = arr[0];
	val = arr[1];
	if (val == NULL)
		val = ft_strdup("");
	str = ft_strjoin(var, ft_strdup("="));
	str = ft_strjoin(str, val);
	unset_one_var(var, my_data);
	ft_lstadd_back(&my_data->envlist, ft_lstnew(str));
	my_data->count++;
}

void	print_variables_list(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !arr[i])
		return ;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(arr[i], STDOUT_FILENO);
		i ++;
	}
}

void	real_export(char **argv, t_envp *my_data)
{
	char	*arr[3];
	int		i;
	char	**temp;

	i = 1;
	temp = NULL;
	arr[0] = NULL;
	arr[1] = NULL;
	arr[2] = NULL;
	while (argv[i] != NULL)
	{
		if (ft_strchr(argv[i], '='))
		{
			if (ft_strcmp(argv[i], "=") != 0)
			{
				temp = ft_split(argv[i], '=');
				if (temp[0])
					arr[0] = ft_strdup(temp[0]);
				if (temp[1])
					arr[1] = ft_strdup(temp[1]);
				free_arr(temp, get_arg_count(temp));
			}
			else
			{
				arr[0] = ft_strdup(argv[i - 1]);
				if (argv[i + 1] != NULL )
					arr[1] = ft_strdup(argv[i + 1]);
			}
			if (!is_valid_var_start(arr[0][0]) || !is_valid_var_char(arr[0]))
			{
				g_exit_status = 1;
				print_export_error(arr[0], arr[2], " : not a valid identifier");
			}
			else
				export_one_var(arr, my_data);
		}
		i ++;
	}
}

/* The double and single quotes wrapping the entire export command
string will be removed by parser/lexer*/
void	exec_export(char **argv, t_envp *my_data)
{
	int	count;
	char	**arr;

	count = 0;
	arr = NULL;
	count = count_non_empty_strings(argv);
	arr = strip_empty_strings(argv);
	g_exit_status = 0;
	if (count == 1 || arr == NULL)
	{
		print_variables_list(my_data->envarr);
		return ;
	}
	else if (count == 2 && arr != NULL)
	{
		if (!ft_strcmp(arr[1], "#"))
		{
			print_variables_list(my_data->envarr);
			return ;
		}
		else if (ft_strchr(arr[1], '='))
			real_export(arr, my_data);
		else if (!is_valid_var_start(arr[1][0]) || !is_valid_var_char(arr[1]))
		{
			g_exit_status = 1;
			print_export_error(arr[1], NULL, " : not a valid identifier");
		}
		else
			return ;
	}
	else
	{
		real_export(arr, my_data);
		return ;
	}
}
