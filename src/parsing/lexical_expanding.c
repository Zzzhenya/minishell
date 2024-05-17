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

int	expand_token_env_1(t_data *data, int i, char **array_split)
{
	int	i_dollar;

	printf(P"1.\n"RS);
	i_dollar = ft_strchr_m(array_split[i], '$');
	if (i_dollar != -1 && array_split[i][i_dollar + 1] == '$')
	{
		data->token[i] = get_pid_string();
		if (data->token[i] == NULL)
			return (-1);
	}
	return (0);
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






	!! remove [OK], expanding [OK] 	one more space print[X]
	" $HOME "a			[X]		 	| /home/tkwak a|

	!! remove [OK], expanding [X]
	"a' '$HOME' 'a"		[X]			a' '/home/tkwak' 'a
	"'$HOME'"			[X]			'/home/tkwak'

	!! NO TOKEN !!
	'' $HOME ''a		[X]			|  /home/tkwak a|
*/
int	expand_env(t_data *data, char **env, int i, int j)
{
	while (data->token[i] != NULL)
	{
		j = 0;
		printf(C"\t[Original] data->token[%d]: %s\n"RS, i, data->token[i]);
		while (data->token[i][j] != '\0')
		{
			printf(Y"\t\t1. data->token[%d][%d]: %c\n"RS, i, j, data->token[i][j]);
			if (data->token[i][j] == '\'')
			{
				printf(P"\t\t\t2-1. Token starts "RED"sq\n"RS);
				data->token[i] = delete_sq(data->token[i]);
				printf(P"\t\t\t2-1. After (sq) delete: %s\n"RS, data->token[i]);
				break ;
			}
			else if (data->token[i][j] == '\"') // i: 1, j: 0
			{
				printf(P"\t\t\t2-2. Token starts "RED"dq\n"RS);
				data->token[i] = delete_dq(data->token[i], data, i, env);
				if (data->token[i] == NULL)
					return (-1);
				printf(P"\t\t\t2-2. After (dq) delete: %s\n"RS, data->token[i]);
				// if (expand_token_env_3(data, i) == -1)
				// 	return (-1);
				// else if (expand_token_env_4(data, env, i) == -1)
				// 	return (-1);
				break ;
			}
			else
			{
				printf(P"\t\t\t2-3. Token starts not quote\n"RS);
				if (expand_token_env_3(data, i) == -1)
					return (-1);
				else if (expand_token_env_4(data, env, i) == -1)
					return (-1);
			}
			j++;
		}
		printf(RED"\n\tToken up\n\n"RS);
		i++;
	}
	return (0);
}

				// if (expand_token_env_1(data, index_token, split_array) == -1)
				// 	return (NULL);
				// else if (expand_token_env_2(env, index_token, split_array) == -1)
				// 	return (NULL);


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
