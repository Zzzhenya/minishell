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
	i_new = ft_strchr_m(row_env, '=') + 1; // let the pointer move to the next position of '=' // HOME= 01234.

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

char	*replace_substring_special(char *token, char *row_env, int i_dollar, int after_space, int index_space)
{
	int		i;
	int		i_new;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(row_env, '=') + 1; // let the pointer move to the next position of '=' // HOME= 01234.


	/* memo */
	printf(P"after_space: %d\n"RS, after_space);
	printf(P"index_space: %d\n"RS, index_space);
	/* memo */


	res = malloc((ft_strlen(row_env + i_new) + i_dollar + 1 + after_space) * sizeof(char));
	if (res == NULL)
		return (NULL);


	// /* memo */
	// printf(P"\nft_strlen(row_env + i_new): %d\n"RS, (int)ft_strlen(row_env + i_new));
	// // 11ea == / h o m e / t k w a k
	// printf(P"i_dollar + 1 + after_space: %d\n\n"RS, i_dollar + 1 + after_space);
	// /* memo */


	printf("1. i_new: %d\n", i_new);
	printf("2. i: %d\n", i);
	while (row_env[i_new] != '\0')
	{
		res[i] = row_env[i_new];
		printf("2. res[%d]: %c\n", i, res[i]);
		i++;
		i_new++;
	}
	printf("\n3. i: %d, i_new: %d\n", i, i_new);
	printf("3-1. token: %s\n\n", token);
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


char	*replace_substring(char *token, char *row_env, int i_dollar, int after_space, int index_space)
{
	int		i;
	int		i_new;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(row_env, '=') + 1; // let the pointer move to the next position of '=' // HOME= 01234.


	/* memo */
	printf(P"after_space: %d\n"RS, after_space);
	printf(P"index_space: %d\n"RS, index_space);
	/* memo */


	res = malloc((ft_strlen(row_env + i_new) + i_dollar + 1 + after_space) * sizeof(char));
	if (res == NULL)
		return (NULL);


	// /* memo */
	// printf(P"\nft_strlen(row_env + i_new): %d\n"RS, (int)ft_strlen(row_env + i_new));
	// // 11ea == / h o m e / t k w a k
	// printf(P"i_dollar + 1 + after_space: %d\n\n"RS, i_dollar + 1 + after_space);
	// /* memo */


	printf("1. i_new: %d\n", i_new);
	while (i < i_dollar)
	{
		printf("1. token[%d]: %c\n", i, token[i]);
		res[i] = token[i];
		i++;
	}
	printf("2. i: %d\n", i);
	while (row_env[i_new] != '\0')
	{
		res[i] = row_env[i_new];
		printf("2. res[%d]: %c\n", i, res[i]);
		i++;
		i_new++;
	}
	printf("\n3. i: %d, i_new: %d\n", i, i_new);
	printf("3-1. token: %s\n\n", token);
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

/*
[ Original ]
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
*/
int	expand_token_env_1(t_data *data, int i, char **array_split)
{
	int	i_dollar;

	printf("\t\t\t"RED"[START]"RS" expand_token_env_"RED"1"RS"\n");
	i_dollar = ft_strchr_m(array_split[i], '$');
	if (i_dollar != -1 && array_split[i][i_dollar + 1] == '$')
	{
		data->token[i] = get_pid_string();
		if (data->token[i] == NULL)
			return (-1);
	}
	printf("\t\t\t"G"[SUCCESS]"RS" expand_token_env_"G"1"RS"\n\n");
	return (0);
}

int	expand_token_env_2(t_data *data, char **env, int i, char **array_split)
{
	int	i_dollar;
	int	row_env;

	printf("\t\t\t"RED"[START]"RS" expand_token_env_"RED"2"RS"\n");
	i_dollar = ft_strchr_m(array_split[i], '$');
	printf(RED"\t\t\t\t1. i_dollar: %d\n"RS, i_dollar);
	printf(RED"\t\t\t\t1. array_split[%d]: %s\n"RS, i, array_split[i]);
	if (i_dollar != -1 && array_split[i][i_dollar + 1] == '\0')
	{
		printf(RED"1. HERE!!!!!!!!1\n");
		return (0);
	}
	else if (i_dollar != -1
		&& (ft_strchr_m(array_split[i], '\'') == -1)
		&& array_split[i][i_dollar + 1] != '?'
		&& array_split[i][i_dollar + 1] != '$')
	{
		printf(RED"2. HERE!!!!!!!!1\n");
		row_env = find_matching_env_row(array_split[i] + i_dollar + 1, env);
		if (row_env == -1)
		{
			array_split[i]
				= replace_substring_1(array_split[i], "", i_dollar);
			printf(RED"\t\t\t\t\tKO"RS", NO ENV\n");
			printf("\t\t\t\t\tarray_split[i]: %s\n", array_split[i]);
		}
		else
		{
			printf("\t\t\t\trow_env: %d\n", row_env); // line of matched 'env'
			int x = i;
			int z = 0;
			int	y = 0;
			while (array_split[x][z])
			{
				if (array_split[x][z] == ' ')
					y = z;
				z++;
			}
			x = z - y;
			printf("x: %d\n", x);
			printf("y: %d\n", y);
			if (y != 0)
				array_split[i]
					= replace_substring(array_split[i], env[row_env], i_dollar, x, y);
			else
				array_split[i]
					= replace_substring_1(array_split[i], env[row_env], i_dollar);
			printf(G"\t\t\t\t\tOK"RS", IN ENV\n");
			printf("\t\t\t\t\tarray_split[i]: %s\n", array_split[i]);
		}
		if (array_split[i] == NULL)
			return (-1);
	}
	else // ex) "'$HOME'"
	{
		printf(RED"3. HERE!!!!!!!!1\n");
		int	length = ft_strlen(array_split[i]);
		int a = i;
		int	c = 0;
		int	d = 0;
		printf("length: %d\n", length);
		char *res1 = (char *)malloc(sizeof(char *) * (length + 1));
		char *res = (char *)malloc(sizeof(char *) * (length + 1));
		while (array_split[a][c] && array_split[a][c] != '$')
		{
			res1[c] = array_split[a][c];
			c++;
		}
		res1[c] = '\0';
		// array_split[a][c] = '\0';
		printf("1.1.1.1.array_split[%d][%d]: %s\n", a, c, array_split[a]);
		printf("a: %d, c: %d\n", a, c);
		printf("current c is position of '$' sign\n");
		c++;
		while (array_split[a][c] != ' ' && array_split[a][c] != '\'')
		{
			res[d] = array_split[a][c];
			c++;
			d++;
		}
		res[d] = '\0';
		printf(B"current 'c': %d\ncurrent 'd': %d\n", c, d);
		// d = 4(End of string), c = 6(start new of array_split[i])

		char *tmp;
		row_env = find_matching_env_row(&res[a], env);
		if (row_env == -1)
		{
			printf("aaa\n");
			return (0);
			array_split[i]
				= replace_substring_1(array_split[i], "", i_dollar);
			printf(RED"\t\t\t\t\tKO"RS", NO ENV\n");
			printf("\t\t\t\t\tarray_split[i]: %s\n", array_split[i]);
		}
		else
		{
			printf(RED"[OK] res: %s\n"RS, res);
			tmp = replace_substring_special(res, env[row_env], i_dollar, d, c);
			printf(P"1111 tmp: %s\n"RS, tmp);
			tmp = ft_strjoin(res1, tmp);
			printf(P"2222 tmp: %s\n"RS, tmp);
		}
		printf(B"11.current 'c': %d\n", c);
		printf(B"11.array_split[a][c]: %c\n", array_split[a][c]);
		d = 0;
		while (array_split[a][c])
		{
			res[d] = array_split[a][c];
			c++;
			d++;
		}
		res[d] = '\0';
		tmp = ft_strjoin(tmp, res);
		printf(P"3333 tmp: %s\n"RS, tmp);
		array_split[i] = tmp;
		printf(RED"4444 array_split[i]: %s\n"RS, array_split[i]);
		if (array_split[i] == NULL)
			return (-1);
	}
	printf("\t\t\t\t\t\t[NO USE]data->token[%d]: %s\n", i, data->token[i]);
	printf("\t\t\t"G"[SUCCESS]"RS" expand_token_env_"G"2"RS"\n\n");
	return (0);
}
/* [ Memo for modify Original ]
	int	expand_token_env_2(t_data *data, char **env, int i)
	{
		int	i_dollar;
		int	row_env;

		i_dollar = ft_strchr_m(data->token[i], '$');
		printf(RED"\t\t\t\t1. i_dollar: %d\n"RS, i_dollar);
		printf(RED"\t\t\t\t1. data->token[%d]: %s\n"RS, i, data->token[i]);
		if (i_dollar != -1 && data->token[i][i_dollar + 1] == '\0')
			return (0);
		else if (i_dollar != -1
			&& (ft_strchr_m(data->token[i], '\'') == -1)
			&& data->token[i][i_dollar + 1] != '?'
			&& data->token[i][i_dollar + 1] != '$')
		{
			row_env = find_matching_env_row(data->token[i] + i_dollar + 1, env);
			if (row_env == -1)
			{
				data->token[i]
					= replace_substring(data->token[i], "", i_dollar);
				printf("1. KO, string isn't in env. data->token[i]: %s\n", data->token[i]);
			}
			else
			{
				data->token[i]
					= replace_substring(data->token[i], env[row_env], i_dollar);
				printf("2. OK, There is string in env. data->token[i]: %s, %s\n", data->token[i], data->token[i+1]);
			}
			if (data->token[i] == NULL)
				return (-1);
		}
		return (0);
	}
*/

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
	printf(RED"\t\t\t\t1. i_dollar: %d\n"RS, i_dollar);
	printf(RED"\t\t\t\t1. data->token[%d]: %s\n"RS, i, data->token[i]);
	if (i_dollar != -1 && data->token[i][i_dollar + 1] == '\0')
		return (0);
	else if (i_dollar != -1
		&& (ft_strchr_m(data->token[i], '\'') == -1)
		&& data->token[i][i_dollar + 1] != '?'
		&& data->token[i][i_dollar + 1] != '$')
	{
		row_env = find_matching_env_row(data->token[i] + i_dollar + 1, env);
		if (row_env == -1)
		{
			data->token[i]
				= replace_substring_1(data->token[i], "", i_dollar);
			printf("1. KO, string isn't in env. data->token[i]: %s\n", data->token[i]);
		}
		else
		{
			data->token[i]
				= replace_substring_1(data->token[i], env[row_env], i_dollar);
			printf("2. OK, There is string in env. data->token[i]: %s, %s\n", data->token[i], data->token[i+1]);
		}
		if (data->token[i] == NULL)
			return (-1);
	}
	return (0);
}




/*	[ TEST ]

	   STR			P/F			RESULT
	--------------------------------
	  $HOME				[O]			/home/tkwak

	 '$HOME'			[O]			 $HOME
	''$HOME''			[O]			 $HOME
	' $HOME 'a			[O]		   | $HOME |a
	'"$HOME"'			[O]			"$HOME"
	  
	 "$HOME"			[O]			/home/tkwak
	""$HOME""			[O]			/home/tkwak
	" $HOME "a			[O]		 	| /home/tkwak a|

	"a' '$HOME' 'a"		[X]			PROBLEM: EXPANDING X
	"'$HOME'"			[X]			PROBLEM: EXPANDING X
*/

/*	[ Original ]
*/
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
			printf(B"\t\t2-2.Delete_dq & expanding\n"RS);
			data->token[i] = delete_dq(data->token[i], data, i, env);
			if (data->token[i] == NULL)
				return (-1);
			printf(B"\t\t2-3.data.token[%d]: %s\n"RS, i, data->token[i]);
			// j++;
			// if (expand_token_env_1(data, i) == -1)
			// 	return (-1);
			// else if (expand_token_env_2(data, env, i) == -1)
			// 	return (-1);
			printf("\tdata.token[%d]: "P"%s"RS"\n", i, data->token[i]);
		}
		else // data->token[i][0] != " || '
		{
			if (expand_token_env_3(data, i) == -1)
				return (-1);
			else if (expand_token_env_4(data, env, i) == -1)
				return (-1);
			printf("\tdata.token[%d]: "P"%s"RS"\n", i, data->token[i]);
		}
		printf("\n");
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
*/

/*	[NOT USED]
	if (remove_single_quotes_from_token(data, i) == -1)
		return (-1);

	int	remove_quotes_from_token(t_data *data, int i)
	{
		printf("\t\t2-1. data->token[%d]: %s\n\n", i, data->token[i]);
		data->token[i] = remove_quote_pairs(data->token[i], data);
		printf("\n\t\t2-2. data->token[%d]: %s\n", i, data->token[i]);
		// if (data->token[i] == NULL)
		// 	return (-1);
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