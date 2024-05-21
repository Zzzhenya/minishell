/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:29:37 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/27 20:29:39 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_checks(t_parse *checks, t_data data)
{
	checks->n_word = 0;
	checks->inword = 0;
	checks->inquote = 0;
	checks->cpy_n_sq = data.n_sq;
	checks->cpy_n_dq = data.n_dq;
	checks->prev = 0;
}

int	count_word(const char *str, t_data data)
{
	t_parse	checks;

	setup_checks(&checks, data);
	while (*str)
	{
		if (*str == ' ' && checks.inquote == 0)
			checks.inword = 0;
		else if ((*str == '<' || *str == '>' || *str == '|')
			&& checks.inquote == 0)
		{
			if (ct_wd_rdr_pipe(&checks, str) == 0)
				return (0);
		}
		else if (*str == '\"' || *str == '\'')
		{
			if (checks.inquote == 1)
				ct_wd_inquote(&checks, str);
			else
				ct_wd_outquote(&checks, str);
		}
		else
			ct_wd_else(&checks);
		str++;
	}
	return (checks.n_word);
}

char	*ft_cpy_str(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_temp_array(char **split_array)
{
	int	j;

	j = 0;
	while (split_array[j] != NULL)
	{
		free(split_array[j]);
		j++;
	}
	free(split_array);
}

/*
	[ For checking ]
	printf(RED"\tn_word: %d\n"RS, data.n_word);
	for (int k = 0; k < data.n_word; k++)
		printf(P"\t\tdata.token[%d]: %s\n"RS, k, data.token[k]);

	[ Delete ]
	(void)env;
*/

int	add_char_to_end(t_data *data, int i, int j)
{
	int len = 0;
	char *temp = NULL;

	if (data->new)
		len = ft_strlen(data->new);
	else
		len = 0;
	temp = malloc(sizeof(char) * (len + 2));
	if (!temp)
		return (-1);
	if (data->new)
		ft_strlcpy(temp, data->new, len + 1);
	temp[len] = data->token[i][j];
	temp[len + 1] = '\0';
	free (data->new);
	data->new = temp;
	return (1);
}

int find_env_var_len(t_data *data, int i, int j, char **env)
{
	int len;

	len = 0;
	(void)env;
	while (data->token[i][j] != '\0')
	{
		if (data->token[i][j] == ' ' || data->token[i][j] == '\"' || data->token[i][j] == '\'')
			break;
		len ++;
		j ++;
	}
	return (len);
}

int	find_copy_env_val(t_data *data, char **env, int i, int j)
{
	char *var;
	int ret = 0;
	int k = 0;
	char **arr;

	ret = find_env_var_len(data, i,  j, env);
	var = NULL;
	var = malloc(sizeof(char) * (ret + 1));
	if (!var)
		return (-1);
	ft_strlcpy(var, data->token[i] + j, ret + 1);
	while (env[k] != NULL)
	{
		arr = ft_split(env[k], '=');
		if (!ft_strncmp(arr[0], var, ft_strlen(var)) && !ft_strncmp(arr[0], var, ft_strlen(arr[0])))
		{
			free (var);
			var = ft_strjoin(data->new, arr[1]);
			free (data->new);
			data->new = var;
			free_arr(arr, get_arg_count(arr));
			return (ret);
		}
		free_arr(arr, get_arg_count(arr));
		k ++;
	}
	free (var);
	var = ft_strjoin(data->new, "");
	free (data->new);
	data->new = var;
	return (ret);
}

void	expand_and_remove_quotes(t_data *data, char **env)
{
	int i = 0;
	int j = 0;
	int ret = 0;

	while (data->token[i] != NULL)
	{
		j = 0;
		data->new = NULL;
		while (data->token[i][j] != '\0')
		{
			if (data->token[i][j] == '\'')
			{
				ret = trim_sq_copy(data, i, j);
				j += ret;
			}
			else if (data->token[i][j] == '$' && data->token[i][j + 1] != '\0')
			{
				ret = find_copy_env_val(data, env, i, j + 1) + 1;
				j += ret;
			}
			else
			{
				ret = add_char_to_end(data, i, j);
				if (ret < 0)
					return ;
				j += ret;
			}
		}
		free (data->token[i]);
		data->token[i] = ft_strdup(data->new);
		printf("%d %s\n", i + 1, data->token[i]);
		free (data->new);
		i++;
	}
}

char	**validate_input(char *user_input, char **env)
{
	t_data	data;

	data.str = user_input;
	if (count_quote(user_input, &data) == -1)
	{
		printf("Syntax error\n");
		return (NULL);
	}
	data.n_word = count_word(data.str, data);
	if (data.n_word == 0)
		return (NULL);
	data.token = NULL;
	data.token = malloc((data.n_word + 1) * sizeof(char *));
	if (data.token == NULL)
		return (NULL);
	if (ft_chopper(&data, data.str, 0, 0) == -1)
		return (NULL);
	(void)env;
	expand_and_remove_quotes(&data, env);
	// if (expand_env(&data, env, 0, 0) == -1)
	// 	return (NULL);
	return (data.token);
}
