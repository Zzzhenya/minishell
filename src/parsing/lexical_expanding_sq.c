/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding_sq.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:38:08 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/16 20:38:12 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_str_by_sq(char *str, int i, int j)
{
	int		start;
	char	**tmp;

	start = 0;
	tmp = (char **)malloc(sizeof(char *) * (100));
	if (tmp == NULL)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == '\'')
			i++;
		start = i;
		while (str[i] && str[i] != '\'')
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
	return (res);
}
