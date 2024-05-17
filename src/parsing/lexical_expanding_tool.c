/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding_tool.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:38:44 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/16 20:38:45 by sde-silv         ###   ########.fr       */
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
	printf("\t\t\t\t3. Delete sq: data->token: %s\n", split_array[i]);
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

int	expand_token_env_5(char **split, int i)
{
	int	i_dollar;

	i_dollar = ft_strchr_m(split[i], '$');
	if (i_dollar != -1 && split[i] != NULL && split[i][i_dollar + 1] != '\0' && split[i][i_dollar + 1] == '$')
	{
		split[i] = get_pid_string();
		if (split[i] == NULL)
			return (-1);
	}
	printf(RED"haha\n"RS);
	return (0);
}

int	expand_token_env_6(char **split, char **env, int i)
{
	int	i_dollar;
	int	row_env;

	i_dollar = ft_strchr_m(split[i], '$');
	if (i_dollar != -1 && split[i] != NULL && split[i][i_dollar + 1] == '\0')
		return (0);
	else if (i_dollar != -1
		&& split[i] != NULL
		&& (ft_strchr_m(split[i], '\'') == -1)
		&& split[i][i_dollar + 1] != '?'
		&& split[i][i_dollar + 1] != '$')
	{
		row_env = find_matching_env_row((split[i]) + i_dollar + 1, env);
		if (row_env == -1)
			split[i]
				= replace_substring_1(split[i], "", i_dollar);
		else
			split[i]
				= replace_substring_1(split[i], env[row_env], i_dollar);
		if (split[i] == NULL)
			return (-1);
	}
	return (0);
}

char	*delete_dq(char *str, t_data *data, int index_token, char **env)
{
	int		j;
	char	*res;
	char	*tmp;
	char	**split_array;

	(void)data;
	(void)index_token;
	(void)env;
	j = 0;
	res = NULL;
	tmp = NULL;
	split_array = split_str_by_dq(str, 0, 0);
	for (int k = 0; split_array[k] != NULL; k++)
		printf("\t\t\t\t3. Delete dq: split_array[%d]: %s\n", k, split_array[k]);
	if (split_array == NULL)
		return (NULL);
	while (split_array[j] != NULL)
	{
		if (expand_token_env_5(&split_array[j], j) == -1)
			return (NULL);
		else if (expand_token_env_6(&split_array[j], env, j) == -1)
			return (NULL);
		// if (expand_token_env_1(data, index_token, split_array) == -1)
		// 	return (NULL);
		// else if (expand_token_env_2(env, index_token, split_array) == -1)
		// 	return (NULL);
		if (res == NULL)
			res = ft_strdup(split_array[j]);
		else
			delete_dq_ext(tmp, res, split_array, j);
		printf("\t\t1. %s\n", split_array[j]);
		if (split_array[j+1] != NULL)
		{
			split_array[j] = ft_strjoin(split_array[j], " ");
			printf("\t\t2. %s\n", split_array[j]);
			res = ft_strdup(split_array[j]);
		}
		j++;
		// printf("\t\t1. %s\n", split_array[j - 1]);
		// if (split_array[j] != NULL)
		// 	split_array[j-1] = ft_strjoin(split_array[j - 1], " ");
		// printf("\t\t2. %s\n", split_array[j - 1]);
	}
	free_temp_array(split_array);
	return (res);
}
