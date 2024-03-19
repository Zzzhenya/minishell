/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:12:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/19 16:15:09 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_matching_env_row(char *str, char **env)
{
	int	i;

	i = 0;
	if (str == NULL && *str == '\0')
		return (-1);
	while (env[i] != NULL)
	{
		if (ft_strcmp(env[i], str) != -1)
			return (i); 
		i++;
	}
	return (-1);
}

char	*trim_single_quotes(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = ft_strlen(str);
	res = (char *)malloc((len - 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	str[len - 1] = '\0';
	while (str[i] != '\0')
	{
		res[i] = str[i + 1];
		i++;
	}
	free(str);
	return (res);
}

int	remove_single_quotes_from_token(t_data *data, int i)
{
	data->token[i] = trim_single_quotes(data->token[i]);
	if (data->token[i] == NULL)
		return (-1);
	return (0);
}

char	*replace_substring(char *token, char *row_env, int i_dollar)
{
	int		i;
	int		i_new;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(row_env, '=') + 1;
	res = malloc((ft_strlen(row_env + i_new) + i_dollar + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < i_dollar)
	{
		res[i] = token[i];
		i++;
	}
	while (row_env[i_new] != '\0')
	{
		res[i] = row_env[i_new];
		i++;
		i_new++;
	}
	res[i] = '\0';
	free(token);
	return (res);
}

int	expand_env(t_data *data, char **env, int i)
{
	int	i_dollar;
	int	row_env;

	while (data->token[i] != NULL)
	{
		i_dollar = ft_strchr_m(data->token[i], '$');
		if (i_dollar != -1
			&& (ft_strchr_m(data->token[i], '\'') == -1) 
			&& data->token[i][i_dollar + 1] != '?' 
			&& data->token[i][i_dollar + 1] != '$')
		{
			row_env = find_matching_env_row(data->token[i] + i_dollar + 1, env);
			if (row_env == -1)
			{
				data->token[i]
					= replace_substring(data->token[i], "\n", i_dollar);
				return (0);
			}
			data->token[i]
				= replace_substring(data->token[i], env[row_env], i_dollar);
			if (data->token[i] == NULL)
				return (-1);
		}
		else if (data->token[i][0] == '\'')
		{
			if (remove_single_quotes_from_token(data, i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
