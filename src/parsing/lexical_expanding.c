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

int	expand_token_env_1(t_data *data, int i)
{
	int	i_dollar;

	i_dollar = ft_strchr_m(data->token[i], '$');
	if (i_dollar != -1 && data->token[i][i_dollar + 1] == '$')
	{
		data->token[i] = get_pid_string();
		if (data->token[i] == NULL)
			return (-1);
	}
	return (0);
}

int	expand_token_env_2(t_data *data, char **env, int i)
{
	int	i_dollar;
	int	row_env;

	i_dollar = ft_strchr_m(data->token[i], '$');
	if (i_dollar != -1 && data->token[i][i_dollar + 1] == '\0')
		return (0);
	else if (i_dollar != -1
		&& (ft_strchr_m(data->token[i], '\'') == -1)
		&& data->token[i][i_dollar + 1] != '?'
		&& data->token[i][i_dollar + 1] != '$')
	{
		row_env = find_matching_env_row(data->token[i] + i_dollar + 1, env);
		// Fixed to like below.
		if (row_env == -1)
		{
			data->token[i]
				= replace_substring(data->token[i], "", i_dollar);
			// printf("1. KO, string isn't in env. data->token[i]: %s\n", data->token[i]);
		}
		else
		{
			data->token[i]
				= replace_substring(data->token[i], env[row_env], i_dollar);
			// printf("2. OK, There is string in env. data->token[i]: %s, %s\n", data->token[i], data->token[i+1]);
		}
		/* Original one
		if (row_env == -1)
			data->token[i]
				= replace_substring(data->token[i], "\n", i_dollar);
		else
			data->token[i]
				= replace_substring(data->token[i], env[row_env], i_dollar);
		*/
		if (data->token[i] == NULL)
			return (-1);
	}
	return (0);
}

int	expand_env(t_data *data, char **env, int i)
{
	while (data->token[i] != NULL)
	{
		if (data->token[i][0] == '\'')
		{
			if (remove_single_quotes_from_token(data, i) == -1)
				return (-1);
		}
		else
		{
			if (expand_token_env_1(data, i) == -1)
				return (-1);
			else if (expand_token_env_2(data, env, i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
