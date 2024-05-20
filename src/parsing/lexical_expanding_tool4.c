/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding_tool4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:12:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/05/17 16:58:14 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* data->tmp = replace_substring_special(data->res, env[data->row_env],
		// 	       data->i_dollar, data->z, data->y);

// char	*replace_substring_special(char *token,
// 	char *row_env, int i_dollar, int after_space, int index_space)*/
char	*replace_substring_special(t_expand *data, char **env, int len)
{
	int		i;
	int		i_new;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(env[data->row_env], '=') + 1;
	len = (ft_strlen(env[data->row_env] + i_new));
	res = malloc((len + data->i_dollar + 1 + data->z) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (env[data->row_env][i_new] != '\0')
	{
		res[i] = env[data->row_env][i_new];
		i++;
		i_new++;
	}
	while (data->res[data->y] != '\0')
	{
		res[i] = data->res[data->y];
		data->y++;
		i++;
	}
	res[i] = '\0';
	free(data->res);
	return (res);
}

int	cpy_until_dollar(char *res, int *i_dollar, char *token)
{
	int	i;

	i = 0;
	while (i < *i_dollar)
	{
		res[i] = token[i];
		i++;
	}
	return (i);
}

int	cpy_env_val(char *res, char *row_env, int i_new, int i)
{
	while (row_env[i_new] != '\0')
	{
		res[i] = row_env[i_new];
		i++;
		i_new++;
	}
	return (i);
}
/*
	while (token[i_dollar + tmp + 1] != '\0')
	{
		res[i] = token[i_dollar + tmp + 1];
		i++;
		tmp++;
	}

*/

int	cpy_after_env_var(char *token, char *res, int j, int i)
{
	while (token[j] != '\0')
	{
		res[i] = token[j];
		i++;
		j++;
	}
	return (i);
}

char	*replace_substring_1(char *token, char *row_env, int i_dollar)
{
	int		i;
	int		i_new;
	int		tmp;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(row_env, '=') + 1;
	tmp = i_new - 1;
	res = malloc((ft_strlen(row_env + i_new)
				+ i_dollar + 1 + 100) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = cpy_until_dollar(res, &i_dollar, token);
	i = cpy_env_val(res, row_env, i_new, i);
	i = cpy_after_env_var(token, res, (i_dollar + tmp + 1), i);
	res[i] = '\0';
	free(token);
	return (res);
}

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
