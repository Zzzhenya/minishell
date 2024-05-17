/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:12:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/05/17 16:58:14 by sde-silv         ###   ########.fr       */
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

char	*get_pid_string(void)
{
	pid_t	pid;

	pid = getpid();
	return (ft_itoa((int)pid));
}

int	expand_token_env_1(t_data *data, int i, char **array_split)
{
	int	i_dollar;

	i_dollar = ft_strchr_m(array_split[i], '$');
	if (i_dollar != -1 && array_split[i][i_dollar + 1] == '$')
	{
		data->token[i] = get_pid_string();
		if (data->token[i] == NULL)
			return (-1);
	}
	return (0);
}

int	expand_token_env_3(t_data *data, int i)
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

void	skip_non_dollar(t_expand *data, char **array_split)
{
	while (array_split[data->x][data->y]
			&& array_split[data->x][data->y] != '$')
	{
		data->res1[data->y] = array_split[data->x][data->y];
		data->y++;
	}
	data->res1[data->y] = '\0';
	data->y++;
}

void	skip_non_space_sq(t_expand *data,
		char **array_split, char **env, int *i)
{
	while (array_split[data->x][data->y] != ' '
			&& array_split[data->x][data->y] != '\'')
	{
		data->res[data->z] = array_split[data->x][data->y];
		data->y++;
		data->z++;
	}
	data->res[data->z] = '\0';
	data->row_env = find_matching_env_row(&data->res[data->x], env);
	if (data->row_env == -1)
	{
		array_split[*i]
			= replace_substring_1(array_split[*i], "", data->i_dollar);
	}
	else
	{
		data->tmp = replace_substring_special(data, env, 0);
		data->tmp = ft_strjoin(data->res1, data->tmp);
		free(data->res1);
	}
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

int	expand_token_env_2(char **env, int i, char **array_split)
{
	t_expand	data;

	init_expand_data_struct(&data);
	data.i_dollar = ft_strchr_m(array_split[i], '$');
	if (data.i_dollar != -1 && array_split[i][data.i_dollar + 1] == '\0')
		return (0);
	else if (data.i_dollar != -1
		&& (ft_strchr_m(array_split[i], '\'') == -1)
		&& array_split[i][data.i_dollar + 1] != '?'
		&& array_split[i][data.i_dollar + 1] != '$')
	{
		expand_replace_substr_if(&data, array_split, &i, env);
		if (array_split[i] == NULL)
			return (-1);
	}
	else
	{
		expand_replace_substr_else(&data, array_split, env, &i);
		if (array_split[i] == NULL)
			return (-1);
	}
	return (0);
}

char	*replace_substring_1(char *token, char *row_env, int i_dollar)
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

/*
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

int	expand_token_env_4(t_data *data, char **env, int i)
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
		if (row_env == -1)
			data->token[i]
				= replace_substring_1(data->token[i], "", i_dollar);
		else
			data->token[i]
				= replace_substring_1(data->token[i], env[row_env], i_dollar);
		if (data->token[i] == NULL)
			return (-1);
	}
	return (0);
}

/*	[ TEST ]

	   STR			P/F			RESULT
	----------------------------------------------------
	  $HOME				[O]			/home/tkwak

	 '$HOME'			[O]			 $HOME
	''$HOME''			[O]			 $HOME
	' $HOME 'a			[O]		   | $HOME |a
	'"$HOME"'			[O]			"$HOME"
	  
	 "$HOME"			[O]			/home/tkwak
	""$HOME""			[O]			/home/tkwak
	" $HOME "a			[O]		 	| /home/tkwak a|

	"a' '$HOME' 'a"		[X]			a' '/home/tkwak' 'a
	"'$HOME'"			[X]			'/home/tkwak'
*/

int	expand_env(t_data *data, char **env, int i, int j)
{
	while (data->token[i] != NULL)
	{
		j = 0;
		while (data->token[i][j] != '\0')
		{
			if (data->token[i][j] == '\'')
				data->token[i] = delete_sq(data->token[i]);
			else if (data->token[i][j] == '\"')
			{
				data->token[i] = delete_dq(data->token[i], data, i, env);
				if (data->token[i] == NULL)
					return (-1);
			}
			else
			{
				if (expand_token_env_3(data, i) == -1)
					return (-1);
				else if (expand_token_env_4(data, env, i) == -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*
int	expand_env(t_data *data, char **env, int i)
{
	int j;

	while (data->token[i] != NULL)
	{
		j = 0;
		if (data->token[i][j] == '\'')
		{
			printf(RED"\t\t1.data.token[%d]: %s\n"RS, i, data->token[i]);
			printf(RED"\t\t1-1.SINGLE QUOTE: NO EXPANSION\n"RS);
			printf(RED"\t\t1-2.Delete_single_quote\n"RS);
			data->token[i] = delete_sq(data->token[i]);
			printf("\tdata.token[%d]: "P"%s"RS"\n", i, data->token[i]);
			// return (0);
		}
		else if (data->token[i][j] == '\"')
		{
			printf(B"\t\t2.data.token[%d]: %s\n"RS, i, data->token[i]);
			printf(B"\t\t2-1.DOUBLE QUOTE: EXPANSION\n"RS);
			int k = j;
			printf("\t\t2-2.k: %d\n", k);
			j++;
			if (expand_token_env_1(data, i) == -1)
				return (-1);
			else if (expand_token_env_2(data, env, i) == -1)
				return (-1);
			// printf(B"\t\t2-2.Delete_double_quote\n"RS);
			// data->token[i] = delete_dq(data->token[i]);
			// j++;
			printf("\tdata.token[%d]: "P"%s"RS"\n", i, data->token[i]);
		}
		else // data->token[i][0] != " || '
		{
			if (expand_token_env_1(data, i) == -1)
				return (-1);
			else if (expand_token_env_2(data, env, i) == -1)
				return (-1);
			printf("\tdata.token[%d]: "P"%s"RS"\n", i, data->token[i]);
		}
		printf("\n");
		i++;
	}
	return (0);
}

	char	*remove_quote_pairs(char *str, t_data *data)
	{
		int i = 0;
		int j = 0;
		char	*res;
		int len = strlen(str);
		// printf("\t\t\tlen: %d, i: %d\n", len, i);
		//int	cpy_n_sq = data->n_sq;
		res = (char *)malloc((len - data->n_sq + 1) * sizeof(char));
		printf("\t\t\tmemsize: %d\n", (len - data->n_sq + 1));
		// printf("\t\t\tlen - cpy_n_q: %d\n", len - cpy_n_sq);
		// printf("\t\t\t2-1-1. cpy_n_sq: %d\n", cpy_n_sq);
		// printf("\t\t\t2-1-1. str: %s\n\n", str);
		// ft_memset(res, '\0', (len- cpy_n_sq + 1));
		while (str[i] != '\0')
		{
			printf("\t\t\t2-1-%d. curr 'i': %d, str[%d]: %c\n", i, i, i, str[i]);
			if (str[i] == '\'')
			{
				i++;
				data->n_sq--;
			}
			else
			{
				res[j] = str[i];
				printf(G"\n\t\t\t\t2-2-%d. res[%d]: %c\n\n"RS, j, j, res[j]);
				j++;
				i++;
			}
			// if (cpy_n_sq == 0)
			// 	break ;
		}
		res[j] = '\0';
		// free(str);
		printf("2-1-2. res: %s\n", res);
		return (res);
	}
*/
