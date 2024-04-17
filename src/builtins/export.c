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

/*if (ft_strcmp(argv[i], "=") != 0)
void	eq_in_own_line(char **argv, int i, t_envp *my_data)
{
	char	*arr[3];
	char	**temp;

	temp = NULL;
	arr[0] = NULL;
	arr[1] = NULL;
	arr[2] = NULL;
	temp = ft_split(argv[i], '=');
	if (temp[0])
		arr[0] = ft_strdup(temp[0]);
	if (temp[1])
		arr[1] = ft_strdup(temp[1]);
	free_arr(temp, get_arg_count(temp));
	if (!is_valid_var_start(arr[0][0]) || !is_valid_var_char(arr[0]))
	{
		g_exit_status = 1;
		print_export_error(arr[0], arr[2], " : not a valid identifier");
	}
	else
		export_one_var(arr, my_data);
	if (arr[0])
		free(arr[0]);
	if (arr[1])
		free(arr[1]);
}*/

/* else 
void	eq_within_string(char **argv, int i, t_envp *my_data)
{
	char	*arr[3];

	arr[0] = NULL;
	arr[1] = NULL;
	arr[2] = NULL;
	if (argv[i-1] != NULL)
		arr[0] = ft_strdup(argv[i - 1]);
	if (argv[i + 1] != NULL)
		arr[1] = ft_strdup(argv[i + 1]);
	if (!is_valid_var_start(arr[0][0]) || !is_valid_var_char(arr[0]))
	{
		g_exit_status = 1;
		print_export_error(arr[0], arr[2], " : not a valid identifier");
	}
	else
		export_one_var(arr, my_data);
	if (arr[0])
		free (arr[0]);
	if (arr[1])
		free (arr[1]);
}

void	real_export(char **argv, t_envp *my_data, int count)
{
	int		i;

	i = 0;
	while (i < count)
	//while (argv[i] != NULL)
	{
		if (ft_strchr(argv[i], '='))
		{*/
			/*if (ft_strcmp(argv[i], "=") != 0)
				eq_in_own_line(argv, i, my_data);
			else*//*
				eq_within_string(argv, i, my_data);
		}
		i ++;
	}
}*/
/*
void	two_argv(char **arr, t_envp *my_data)
{
	if (!ft_strcmp(arr[0], "#"))
	{
		print_variables_list(my_data->envarr);
		return ;
	}
	else if (ft_strchr(arr[0], '='))
		real_export(arr, my_data);
	else if (!is_valid_var_start(arr[0][0]) || !is_valid_var_char(arr[0]))
	{
		g_exit_status = 1;
		print_export_error(arr[1], NULL, " : not a valid identifier");
	}
	else
		return ;
}*/

/* The double and single quotes wrapping the entire export command
string will be removed by parser/lexer
export, export "", export '' - 0
export #, export "#", export '#' - 1
export hello, "hello", ""hello"" - 1
export hello=one - 1
export hello= - 2
export "hello=" - 1
export "hello=one" - 1
export ""hello=one"" - 3
*/

/*
	// if char is not in string -> return NULL
	// if char is at the end of string -> last string is an empty string
	// always have two strings

*/

char **split_at_first_occ(char *str, char c)
{

	int i = 0;
	int loc = 0;
	int len = 0;
	char **arr;

	arr = NULL;
	len = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			loc = i;
			break;
		}
		i ++;
	}
	arr = (char **)malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	arr[0] = malloc(sizeof(char) * loc + 1);
	if (!arr[0])
	{
		free (arr);
		return (NULL);
	}
	ft_strlcpy(arr[0], str, loc + 1);
	if (loc + 1 == '\0')
		arr[1] = ft_strdup("");
	else
	{
		arr[1] = malloc(sizeof(char) * (len - loc));
		if (!arr[1])
		{
			free (arr);
			return (NULL);
		}
		ft_strlcpy(arr[1], str + loc + 1, (len - loc));
	}
	arr[2] = NULL;
	return (arr);
}

void	multi_export(char **argv, t_envp *my_data, int count)
{
	int		i;
	char	*str;
	char	**arr;

	i = 0;
	str = NULL;
	arr = NULL;
	while (i < count)
	{
		str = ft_strchr(argv[i], '=');
		if (str && argv[i][0] != '=')
		{
			arr = split_at_first_occ(argv[i], '=');
			if (!is_valid_var_start(arr[0][0]) || !is_valid_var_char(arr[0]))
			{
				g_exit_status = 1;
				print_export_error(arr[0], NULL, " : not a valid identifier");
			}
			else
				export_one_var(arr, my_data);
			free_arr(arr, get_arg_count(arr));
		}
		else
		{
			if (!is_valid_var_start(argv[i][0]) || !is_valid_var_char(argv[i]))
			{
				g_exit_status = 1;
				print_export_error(argv[i], NULL, " : not a valid identifier");
			}
		}
		i ++;
	}
}

void	exec_export(char **argv, t_envp *my_data)
{
	
	int		count;
	char	**arr;

	//(void)my_data;
	count = 0;
	arr = NULL;
	count = count_non_empty_strings(&argv[1]);
	arr = strip_empty_strings(&argv[1]);
	g_exit_status = 0;
	if (count == 0)
		print_variables_list(my_data->envarr);
	else
		multi_export(arr, my_data, count);
	if (arr)
		free_arr(arr, count);
}