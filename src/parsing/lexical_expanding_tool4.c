/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding_tool4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:12:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/05/18 09:25:11 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	[ TEST ]
	printf(RED"\tres: %s\n"RS, res);
	printf(B"res[%d]: %s\n"RS, i, res);
	printf(B"token[%d]: %s\n"RS, i, token+1);

	printf("res[%d]: %c\n", i, res[i]);
	printf("token[%d]: %c\n", i, token[i]);

	while (env[data->row_env][i_new] != '\0')
	{
		res[j] = env[data->row_env][i_new];
		j++;
		i_new++;
	}
*/
void	replace_substring_cpy_iter(char *src, int *cpy, int *i, char *dest)
{
	while (src[*i] != '\0')
	{
		dest[*cpy] = src[*i];
		(*cpy)++;
		(*i)++;
	}
}
/*
		array_split[*i] = replace_substring(array_split, i, env, data);
			= replace_substring(array_split[*i],
				env[data->row_env], data->i_dollar, data->x, data->y);
		// char	*replace_substring(char *token,
// 	char *row_env, int i_dollar, int after_space, int index_space)
*/

/*
	else if (split_array[j][0] == '\'')
	res = ft_strjoin(res, delete_sq(split_array[j]));
*/
char	*delete_dq_only(char *str)
{
	int		j;
	char	*res;
	char	*tmp;
	char	**split_array;

	j = 0;
	res = NULL;
	tmp = NULL;
	split_array = split_str_by_dq(str, 0, 0);
	if (split_array == NULL)
		return (NULL);
	else if (split_array[j] == NULL)
		res = ft_strdup("");
	while (split_array[j] != NULL)
	{
		if (res == NULL)
			res = ft_strdup(split_array[j]);
		else
			delete_dq_ext(tmp, res, split_array, j);
		j++;
	}
	free_temp_array(split_array);
	return (res);
}

int	delete_sq_norm(t_data *data, char **env, int i, int j)
{
	if (data->token[i][j] == '\'')
	{
		data->token[i] = delete_sq(data->token[i]);
		if (data->token[i][0] == '\"' && data->token[i][1] == '\"')
			data->token[i] = delete_dq_only(data->token[i]);
		return (0);
	}
	else if (data->token[i][j] == '\"')
	{
		data->token[i] = delete_dq(data->token[i], env, 0);
		if (data->token[i][0] == '\'' && data->token[i][1] == '\'')
			data->token[i] = delete_sq(data->token[i]);
		return (0);
	}
	return (-1);
}
