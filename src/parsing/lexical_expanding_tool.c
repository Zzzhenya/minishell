/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding_tool.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:15:54 by tkwak             #+#    #+#             */
/*   Updated: 2024/05/21 10:15:55 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	get an array of strings split by sq
	duplicate the array
*/
char	*delete_sq(char *str)
{
	char	*res;
	char	**split_array;

	res = NULL;
	split_array = split_str_by_sq(str, 0, 0);
	if (split_array == NULL)
		return (NULL);
	res = dup_array(split_array, res);
	free_temp_array(split_array);
	if (res == NULL)
		res = ft_strdup("");
	free (str);
	return (res);
}

/*
char	*delete_sq(char *str)
{
	int		i;
	char	*res;
	char	*tmp;
	char	**split_array;

	i = 0;
	res = NULL;
	split_array = split_str_by_sq(str, 0, 0);
	if (split_array == NULL)
		return (NULL);
	while (split_array[i] != NULL)
	{
		if (res == NULL)
			res = strdup(split_array[i]);
		else
		{
			tmp = strdup(res);
			free(res);
			res = ft_strjoin(tmp, split_array[i]);
			free(tmp);
		}
		i++;
	}
	free_temp_array(split_array);
	if (res == NULL)
		res = ft_strdup("");
	return (res);
}
*/

char	**split_str_by_dq(char *str, int i, int j)
{
	int		start;
	char	**tmp;

	start = 0;
	tmp = (char **)malloc(sizeof(char *) * (100));
	if (tmp == NULL)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == '\"')
			i++;
		start = i;
		while (str[i] && str[i] != '\"')
			i++;
		if (i > start)
		{
			tmp[j] = (char *)malloc(sizeof(char) * ((i - start) + 1));
			if (tmp[j] == NULL)
				return (NULL);
			ft_cpy_str(tmp[j], &str[start], i - start);
			j++;
		}
	}
	tmp[j] = NULL;
	return (tmp);
}

char	*delete_dq_ext(char *res, char **split_array, int j)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(res);
	free(res);
	res = ft_strjoin(tmp, split_array[j]);
	free(tmp);
	return (res);
}

/*
	[ TEST ]
	for (int k = 0; split_array[k] != NULL; k++)
	printf("\t\t\t\t3. Delete dq: split_array[%d]: %s\n", k, split_array[k]);

	int k = 0;
	while (split_array[k])
	{
		printf("split_array[%d]: %s\n", k, split_array[k]);
		k++;
	}

	free_temp_array(split_array);

	echo "abab""a''a'"''
*/
char	*norm_line(char **split_array, char **env, int j, char *res)
{
	while (split_array[j] != NULL)
	{
		if (expand_token_env_5(&split_array[j], j) == -1)
			return (NULL);
		else if (expand_token_env_6(&split_array[j], env, j) == -1)
			return (NULL);
		if (res == NULL)
			res = ft_strdup(split_array[j]);
		else if (split_array[j][0] == '\'')
		{
			split_array[j] = delete_sq(split_array[j]);
			res = ft_strjoin(res, split_array[j]);
		}
		else
			res = delete_dq_ext(res, split_array, j);
		free(split_array[j]);
		j++;
	}
	return (res);
}

char	*delete_dq(char *str, char **env, int j, char *res)
{
	char	**split_array;

	split_array = NULL;
	if (str != NULL)
		split_array = split_str_by_dq(str, 0, 0);
	if (split_array == NULL)
		return (NULL);
	else if (split_array[j] == NULL)
		res = ft_strdup("");
	res = norm_line (split_array, env, j, res);
	free_together (split_array, str);
	return (res);
}
/*
char	*delete_dq(char *str, char **env, int j, char *res)
{
	char	**split_array;

	split_array = NULL;
	if (str != NULL)
		split_array = split_str_by_dq(str, 0, 0);
	if (split_array == NULL)
		return (NULL);
	else if (split_array[j] == NULL)
		res = ft_strdup("");
	while (split_array[j] != NULL)
	{
		if (expand_token_env_5(&split_array[j], j) == -1)
			return (NULL);
		else if (expand_token_env_6(&split_array[j], env, j) == -1)
			return (NULL);
		if (res == NULL)
			res = ft_strdup(split_array[j]);
		else if (split_array[j][0] == '\'')
		{
			split_array[j] = delete_sq(split_array[j]);
			res = ft_strjoin(res, split_array[j]);
		}
		else
			res = delete_dq_ext(res, split_array, j);
		free(split_array[j]);
		j++;
	}
	free_together (split_array, str);
	return (res);
}
*/
