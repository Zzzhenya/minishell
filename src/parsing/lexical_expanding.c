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

char	*replace_substring_special(char *token,
	char *row_env, int i_dollar, int after_space, int index_space)
{
	int		i;
	int		i_new;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(row_env, '=') + 1;
	res = malloc((ft_strlen(row_env + i_new) + i_dollar + 1 + after_space)
			* sizeof(char));
	if (res == NULL)
		return (NULL);
	while (row_env[i_new] != '\0')
	{
		res[i] = row_env[i_new];
		i++;
		i_new++;
	}
	while (token[index_space] != '\0')
	{
		res[i] = token[index_space];
		index_space++;
		i++;
	}
	res[i] = '\0';
	free(token);
	return (res);
}

char	*replace_substring(char *token,
	char *row_env, int i_dollar, int after_space, int index_space)
{
	int		i;
	int		i_new;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(row_env, '=') + 1;
	res = malloc((ft_strlen(row_env + i_new) + i_dollar + 1 + after_space)
			* sizeof(char));
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
	while (token[index_space] != '\0')
	{
		res[i] = token[index_space];
		index_space++;
		i++;
	}
	res[i] = '\0';
	free(token);
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

int	expand_token_env_2(t_data *data, char **env, int i, char **array_split)
{
	int		i_dollar;
	int		row_env;
	int		x;
	int		z;
	int		y;
	int		length;
	char	*res1;
	char	*res;
	char	*tmp;

	(void)data;
	i_dollar = ft_strchr_m(array_split[i], '$');
	if (i_dollar != -1 && array_split[i][i_dollar + 1] == '\0')
		return (0);
	else if (i_dollar != -1
		&& (ft_strchr_m(array_split[i], '\'') == -1)
		&& array_split[i][i_dollar + 1] != '?'
		&& array_split[i][i_dollar + 1] != '$')
	{
		row_env = find_matching_env_row(array_split[i] + i_dollar + 1, env);
		if (row_env == -1)
		{
			array_split[i]
				= replace_substring_1(array_split[i], "", i_dollar);
		}
		else
		{
			x = i;
			z = 0;
			y = 0;
			while (array_split[x][z])
			{
				if (array_split[x][z] == ' ')
					y = z;
				z++;
			}
			x = z - y;
			if (y != 0)
				array_split[i]
					= replace_substring(array_split[i],
						env[row_env], i_dollar, x, y);
			else
				array_split[i]
					= replace_substring_1(array_split[i],
						env[row_env], i_dollar);
		}
		if (array_split[i] == NULL)
			return (-1);
	}
	else
	{
		length = ft_strlen(array_split[i]);
		x = i;
		y = 0;
		z = 0;
		res1 = (char *)malloc(sizeof(char *) * (length + 1));
		res = (char *)malloc(sizeof(char *) * (length + 1));
		while (array_split[x][y] && array_split[x][y] != '$')
		{
			res1[y] = array_split[x][y];
			y++;
		}
		res1[y] = '\0';
		y++;
		while (array_split[x][y] != ' ' && array_split[x][y] != '\'')
		{
			res[z] = array_split[x][y];
			y++;
			z++;
		}
		res[z] = '\0';
		row_env = find_matching_env_row(&res[x], env);
		if (row_env == -1)
		{
			array_split[i]
				= replace_substring_1(array_split[i], "", i_dollar);
		}
		else
		{
			tmp = replace_substring_special(res, env[row_env], i_dollar, z, y);
			tmp = ft_strjoin(res1, tmp);
			free(res1);
		}
		z = 0;
		while (array_split[x][y])
		{
			res[z] = array_split[x][y];
			y++;
			z++;
		}
		res[z] = '\0';
		tmp = ft_strjoin(tmp, res);
		free(res);
		array_split[i] = tmp;
		if (array_split[i] == NULL)
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
int	expand_env(t_data *data, char **env, int i)
{
	int	j;

	while (data->token[i] != NULL)
	{
		j = 0;
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