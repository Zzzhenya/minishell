/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding_dq.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:38:44 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/16 20:38:45 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	delete_dq_ext(char *tmp, char *res, char **split_array, int j)
{
	tmp = ft_strdup(res);
	free(res);
	res = ft_strjoin(tmp, split_array[j]);
	free(tmp);
}

char	*delete_dq(char *str, t_data *data, int index_token, char **env)
{
	int		j;
	char	*res;
	char	*tmp;
	char	**split_array;

	res = NULL;
	tmp = NULL;
	split_array = split_str_by_dq(str, 0, 0);
	if (split_array == NULL)
		return (NULL);
	j = 0;
	while (split_array[j] != NULL)
	{
		if (expand_token_env_1(data, index_token, split_array) == -1)
			return (NULL);
		else if (expand_token_env_2(data, env, index_token, split_array) == -1)
			return (NULL);
		if (res == NULL)
			res = ft_strdup(split_array[j]);
		else
			delete_dq_ext(tmp, res, split_array, j);
		j++;
	}
	free_temp_array(split_array);
	return (res);
}
