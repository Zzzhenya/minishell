/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding_tool3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:12:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/05/17 16:58:14 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_expand_data_struct(t_expand *data)
{
	data->i_dollar = 0;
	data->row_env = 0;
	data->x = 0;
	data->z = 0;
	data->y = 0;
	data->length = 0;
	data->res1 = NULL;
	data->res = NULL;
	data->tmp = NULL;
}

/*
char	*replace_substring(char **array_split, int *i, char **env,
		t_expand *data)
*/
void	expand_replace_substr_if1(t_expand *data, char **array_split,
			char **env, int *i)
{
	data->x = *i;
	data->z = 0;
	data->y = 0;
	while (array_split[data->x][data->z])
	{
		if (array_split[data->x][data->z] == ' ')
			data->y = data->z;
		data->z++;
	}
	data->x = data->z - data->y;
	if (data->y != 0)
		array_split[*i] = replace_substring(array_split, i, env, data);
	else
		array_split[*i]
			= replace_substring_1(array_split[*i],
				env[data->row_env], data->i_dollar);
}

void	expand_replace_substr_else(t_expand *data,
			char **array_split, char **env, int *i)
{
	data->length = ft_strlen(array_split[*i]);
	data->x = *i;
	data->y = 0;
	data->z = 0;
	data->res1 = (char *)malloc(sizeof(char *) * (data->length + 1));
	data->res = (char *)malloc(sizeof(char *) * (data->length + 1));
	skip_non_dollar(data, array_split);
	skip_non_space_sq(data, array_split, env, i);
	data->z = 0;
	while (array_split[data->x][data->y])
	{
		data->res[data->z] = array_split[data->x][data->y];
		data->y++;
		data->z++;
	}
	data->res[data->z] = '\0';
	data->tmp = ft_strjoin(data->tmp, data->res);
	free(data->res);
	array_split[*i] = data->tmp;
}

/*
		data.row_env = find_matching_env_row(array_split[i]
				+ data.i_dollar + 1, env);
		if (data.row_env == -1)
			array_split[i]
				= replace_substring_1(array_split[i], "", data.i_dollar);
		else
			expand_replace_substr_if1(&data, array_split, env, &i);
*/
void	expand_replace_substr_if(t_expand *data, char **array_split,
			int *i, char **env)
{
	data->row_env = find_matching_env_row(array_split[*i]
			+ data->i_dollar + 1, env);
	if (data->row_env == -1)
		array_split[*i]
			= replace_substring_1(array_split[*i], "", data->i_dollar);
	else
		expand_replace_substr_if1(data, array_split, env, i);
}

char	*replace_substring(char **array_split, int *i, char **env,
		t_expand *data)
{
	int		j;
	int		i_new;
	char	*res;

	j = 0;
	i_new = ft_strchr_m(env[data->row_env], '=') + 1;
	res = malloc((ft_strlen(env[data->row_env] + i_new)
				+ data->i_dollar + 1 + data->x) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (j < data->i_dollar)
	{
		res[j] = array_split[*i][j];
		j++;
	}
	replace_substring_cpy_iter(env[data->row_env], &j, &i_new, res);
	while (array_split[*i][data->y] != '\0')
	{
		res[j] = array_split[*i][data->y];
		data->y++;
		j++;
	}
	res[j] = '\0';
	free(array_split[*i]);
	return (res);
}
