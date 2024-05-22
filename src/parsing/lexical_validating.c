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

int find_env_var_len(t_data *data, int i, int j)
{
	int len;

	len = 0;
	while (data->token[i][j] != '\0')
	{
		if (data->token[i][j] == ' ' || data->token[i][j] == '\"' || data->token[i][j] == '\'' || data->token[i][j] == '$')
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

	ret = find_env_var_len(data, i,  j);
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

int count_letters(char *str, char skip)
{
	int count = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] != '\0' && str[i] == skip)
			i ++;
		while (str[i] != '\0' && str[i] != skip)
		{
			i ++;
			count ++;
		}
		if (str[i] != '\0' && str[i] == skip)
			break;
	}
	return (count);
}

int trim_sq_copy(t_data *data, int i, int j)
{
	int ret = 0;
	int len = 0;
	char *str = NULL;
	char *join = NULL;
	int k = 0;

	len = count_letters(data->token[i] + j, '\'');
	str = malloc (sizeof(char) * len + 1);
	while (data->token[i][j] != '\0')
	{
		if (data->token[i][j] != '\0' && data->token[i][j] == '\'')
		{
			ret ++;
			j ++;
		}
		while (data->token[i][j] != '\0' && data->token[i][j] != '\'')
		{
			str[k] = data->token[i][j];
			k ++;
			ret ++;
			j ++;
		}
		if (data->token[i][j] != '\0' && data->token[i][j] == '\'')
		{
			str[k] = '\0';
			ret ++;
			j ++;
			break;
		}
	}
	join = ft_strjoin(data->new, str);
	free (data->new);
	free (str);
	data->new = join;
	return (ret);
}

int trim_dq_copy(t_data *data, int i, int j, char *dqstr)
{
	int ret = 0;
	//int len = 0;
	//char *str = NULL;
	int k = 0;

	while (data->token[i][j] != '\0')
	{
		if (data->token[i][j] != '\0' && data->token[i][j] == '\"')
		{
			ret ++;
			j ++;
		}
		while (data->token[i][j] != '\0' && data->token[i][j] != '\"')
		{
			dqstr[k] = data->token[i][j];
			k ++;
			ret ++;
			j ++;
		}
		if (data->token[i][j] != '\0' && data->token[i][j] == '\"')
		{
			dqstr[k] = '\0';
			ret ++;
			j ++;
			return (ret);
		}
	}
	return (ret);
}

int dq_env_var_len(char *temp, int i)
{
	int len = 0;

	if (temp[i] == '$')
	{
		i ++;
		while (temp[i] != '\0')
		{
			if (temp[i] == ' ' || temp[i] == '\"' || temp[i] == '\'' || temp[i] == '$')
				break;
			len ++;
			i ++;
		}
	}
	return (len);
}

int dq_env(char *dqstr,char *temp,int i,char **env)
{
	char *var;
	int var_len = 0;
	int j = 0;
	char **arr = NULL;

	var = NULL;
	j = i;
	while (temp[j] != '\0')
	{
		if (temp[j] == ' ' || temp[j] == '$' || temp[j] == '\'' || temp[j] == '\"')
			break;
		j ++;
		var_len++;
	}
	var = malloc(sizeof(char) * (var_len + 1));
	ft_strlcpy(var, temp + 1, var_len + 1);
	j = 0;
	while (env[j] != NULL)
	{
		arr = ft_split(env[j], '=');
		if (!ft_strncmp(arr[0], var, ft_strlen(var)))
		{
			free(var);
			var = NULL;
			var = ft_strdup(dqstr);
			free (dqstr);
			dqstr = ft_strjoin(var, arr[1]);
			free (var);
			free_arr(arr, get_arg_count(arr));
			return (var_len);
		}
		free_arr(arr, get_arg_count(arr));
		arr = NULL;
		j ++;
	}
	free(var);
	var = ft_strdup(dqstr);
	free (dqstr);
	dqstr = ft_strjoin(var, "");
	free (var);
	return (var_len);
}

/*

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

*/

int dq_copy_char(char *dqstr, char *temp, int i)
{
	int len = 0;
	char *join = NULL;

	if (dqstr)
		len = ft_strlen(dqstr);
	else
		len = 0;
	join = malloc(sizeof(char) * (len + 2));
	if (!join)
		return (-1);
	if (dqstr)
		ft_strlcpy(join, dqstr, len + 1);
	join[len] = temp[i];
	join[len + 1] = '\0';
	//free (dqstr);
	dqstr = ft_strdup(join);
	free (join);
	return (1);

}

void	dq_find_copy_env(char *dqstr, char **env, t_data *data)
{
	int i = 0;
	int ret = 0;
	char *join = NULL;

	
	char *temp = NULL;
	temp = ft_strdup(dqstr);
	while (temp[i] != '\0')
	{
		if (temp[i] == '$' && temp[i + 1] != '\0')
		{
			i ++;
			ret = dq_env(dqstr, temp, i, env);
			i += ret;
		}
		else
		{
			ret = dq_copy_char(dqstr, temp, i);
			i += ret;
		}
	}
	// if (data->new)
	// 	join = ft_strjoin(data->new, dqstr);
	// else
		join = ft_strdup(dqstr);
	free (data->new);
	data->new = ft_strdup(join);
	free (join);
}

int trim_dq_expand_copy(t_data *data, int i, int j, char **env)
{
	int ret;
	char *join = NULL;
	int len = 0;
	char *dqstr = NULL;

	len = count_letters(data->token[i] + j, '\"');
	dqstr = malloc (sizeof(char) * len + 1);
	ret = trim_dq_copy(data, i, j, dqstr);
	if (!(ft_strchr(dqstr, '$')))
	{
		if (data->new)
			join = ft_strjoin(data->new, dqstr);
		else
			join = ft_strdup(dqstr);
		free (data->new);
		free (dqstr);
		data->new = join;
		return (ret);
	}
	else
	{
		dq_find_copy_env(dqstr, env, data);
		// if (data->new)
		// 	join = ft_strjoin(data->new, dqstr);
		// else
		// 	join = ft_strdup(dqstr);
		// free (data->new);
		// data->new = join;
		return (ret);
	}
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
			else if (data->token[i][j] == '\"')
			{
				ret = trim_dq_expand_copy(data, i, j, env);
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
	expand_and_remove_quotes(&data, env);
	// if (expand_env(&data, env, 0, 0) == -1)
	// 	return (NULL);
	return (data.token);
}
