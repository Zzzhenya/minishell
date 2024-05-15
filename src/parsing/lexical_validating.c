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

int	count_word(const char *str, int n_word, int inword, int inquote, t_data data)
{
	char prev;

	prev = 0;
	/* memo */
	// if (data.n_sq > 0 || data.n_dq > 0)
	// 	printf("\nn_dq: %d\nn_sq: %d\n", data.n_dq, data.n_sq);
	// else
	// 	printf("2. There is no quotes in the string.\n");
	/* memo */

	int	cpy_n_sq = data.n_sq;
	int	cpy_n_dq = data.n_dq;
	/* memo */
	// printf(C"\n[1] How does 'USER_INPUT' consist?\n\n"RS);
	// printf("\t*str	inquote	inword	prev_quote  n_word   cpy_n_sq   cpy_n_dq\n");
	// printf("\t%c	   %d	   %d	   %c	     %d		%d	  %d\n\n", *str, inquote, inword, prev, n_word, cpy_n_sq, cpy_n_dq);
	/* memo */

	while (*str)
	{
		if (*str == ' ' && inquote == 0)
			inword = 0;
		else if (*str == '<' && inquote == 0)
		{
			if (*(str + 1) == '<')
			{
				str++;
				if (*(str + 1) != '<')
				{
					n_word++;
					inword = 0;
				}
				else
				{
					g_exit_status = 2;
					printf("Syntax error\n");
					return (0);
				}
			}
			else
			{
				n_word++;
				inword = 0;
			}
		}
		else if (*str == '>' && inquote == 0)
		{
			if (*(str + 1) == '>')
			{
				str++;
				if (*(str + 1) != '>')
				{
					n_word++;
					inword = 0;
				}
				else
				{
					g_exit_status = 2;
					printf("Syntax error\n");
					return (0);
				}
			}
			else
			{
				n_word++;
				inword = 0;
			}
		}
		else if (*str == '|' && inquote == 0)
		{
			n_word++;
			inword = 0;
		}
		// else if ((*str == '<' || *str == '>' || *str == '|') && inquote == 0)
		// {
		// 	n_word++;
		// 	inword = 0;
		// }
		else if (*str == '\"' || *str == '\'')
		{
			if (inquote == 1) // Already in 'quote' // ' ' ' '
			{
				/* memo */
				// printf(G"IN QUOTE\n"RS);
				/* memo */
				if (prev != *str) // ' != "
				{
					if (prev == 0)
					{
						prev = *str;
						n_word++;
						inquote = 1;
						inword = 1;
					}
					else
					{
						if (*str == '\'' && prev != '\"')
							cpy_n_sq--;
						else if (*str == '\"' && prev != '\'')
							cpy_n_dq--;
					}
				}
				else // prev quote type == current quote type (ex) "double = "double
				{
					/* memo */
					// printf(G"Prev quote type = curr quote type\n"RS);
					/* memo */
					if (*str == '\"')
					{
						if (*(str + 1) == ' ' && (cpy_n_dq % 2 != 0))
						{
							/* memo */
							// printf(RED"Reset everything, cause quote is pair and next is 'space'\n"RS);
							/* memo */
							inword = 0;
							inquote = 0;
							prev = 0;
						}
						else if (ft_isalpha(*(str + 1)))
						{
							/* memo */
							// printf("Next char is alphabet\n");
							/* memo */
							if (cpy_n_dq % 2 != 0) // 5
							{
								inquote = 0;
								prev = 0;
							}
							else
							{
								inword = 1;
								inquote = 1;
							}
						}
						if (prev != '\'')
							cpy_n_dq--;
					}
					else // *str == \'
					{
						if (*(str + 1) == ' ' && (cpy_n_sq % 2 != 0))
						{
							/* memo */
							// printf(RED"Reset everything, cause quote is pair and next is 'space'\n"RS);
							/* memo */

							inword = 0;
							inquote = 0;
							prev = 0;
							// cpy_n_sq--;
						}
						else if (ft_isalpha(*(str + 1)))
						{
							/* memo */
							// printf("Next char is alphabet\n");
							/* memo */
							if (cpy_n_sq % 2 != 0) // 5
							{
								inquote = 0;
								prev = 0;
							}
							else
							{
								inword = 1;
								inquote = 1;
							}
						}
						if (prev != '\"')
							cpy_n_sq--;
					}
					//}
				}
			}
			else // Not in quote: inquote == 0, start in 'quote' (' or ")
			{
				/* memo */
				// printf(RED"NOT IN QUOTE YET\n"RS);
				/* memo */
				prev = *str; // save ' or " for prev
				if (*str == '\'')
				{
					/* memo */
					// printf(G"START SINGLE QUOTE\n"RS);
					/* memo */
					if (inword == 0)
						n_word++;
					cpy_n_sq--;
				}
				else if (*str == '\"')
				{
					/* memo */
					// printf(G"START DOUBLE QUOTE\n"RS);
					/* memo */
					if (inword == 0)
						n_word++;
					cpy_n_dq--;
				}
				inquote = 1;
				inword = 1;
			}
		}
		else // NOT(5): SPACE > | " '
		{
			if (inword == 0)
			{
				n_word++;
				inword = 1;
			}
		}
		/* memo */
		// printf("\t%c	   %d	   %d	   %c	     %d		%d	  %d\n", *str, inquote, inword, prev, n_word, cpy_n_sq, cpy_n_dq);
		// printf("-------------------------------------------------------------------------\n");
		/* memo */
		str++;
	}
	return (n_word);
}

/* norminette later */
char	*ft_cpy_str(char *dest, char *src, int len)
{
 	int i = 0;

 	while (i < len)
 	{
 		dest[i] = src[i];
 		i++;
 	}
 	dest[i] = '\0';
 	return(dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*res;

	if (s1 && s2)
	{
		len1 = strlen(s1);
		len2 = strlen(s2);
		res = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
		if (res == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			res[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			res[len1] = s2[i];
			len1++;
		}
		res[len1] = '\0';
		return (res);
	}
	return (NULL);
}

char	**split_str_by_sq(char *str)
{
	int 	i;
	int 	j;
	int 	start;
	char	**tmp;

	i = 0;
	j = 0;
	start = 0;
	// printf(C"\tSplit string by single quote\n"RS);
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
	split_array = split_str_by_sq(str);
	if (split_array == NULL)
		return (NULL);
	while (split_array[i] != NULL)
	{
		if (res == NULL)
			res = strdup(split_array[i]);	// Cpy first TOKEN
		else
		{
			tmp = strdup(res);	// cpy 'res' to 'tmp'
			free(res);
			res = ft_strjoin(tmp, split_array[i]);
			free(tmp);
		}
		i++;
	}
	for (int k = 0; split_array[k] != NULL; k++)
		free(split_array[k]);
	free(split_array);
	return (res);
}

char	**split_str_by_dq(char *str)
{
	int 	i;
	int 	j;
	int 	start;
	char	**tmp;

	i = 0;
	j = 0;
	start = 0;
	printf(C"\n\t\tSplit string by dq\n"RS);
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

char	*delete_dq(char *str, t_data *data, int index_token, char **env)
{
	int		i;
	char	*res;
	char	*tmp;
	char	**split_array;

	i = 0;
	res = NULL;
	split_array = split_str_by_dq(str);
	if (split_array == NULL)
		return (NULL);


	/* memo */
	printf("\n");
	int j = 0;
	while (split_array[j] != NULL)
	{
		printf(G"\t\tsplit_array[%d]: %s\n"RS, j, split_array[j]);
		j++;
	}
	/* memo */

	/* memo */
	j = 0;
	while (split_array[j] != NULL)
	{
		printf("\t\t\t'j': %d\n", j);
		if (expand_token_env_1(data, index_token, split_array) == -1)
			return (NULL);
		else if (expand_token_env_2(data, env, index_token, split_array) == -1)
			return (NULL);
		if (res == NULL)
		{
			printf(P"\t\t\t\tStart: split_array[%d]: %s\n"RS, j, split_array[j]);
			res = strdup(split_array[j]);	// Cpy first TOKEN
			printf(P"\t\t\t\tres: %s\n"RS, res);
		}
		else
		{
			tmp = strdup(res);	// cpy 'res' to 'tmp'
			free(res);
			printf(RED"\t\t\t\tWihle: split_array[%d]: %s\n"RS, j, split_array[j]);
			res = ft_strjoin(tmp, split_array[j]);
			printf(RED"\t\t\t\tres: %s\n"RS, res);
			free(tmp);
		}
		j++;
	}
	// [ Original ]
	// int j = 0;
	// while (split_array[j] != NULL)
	// {
	// 	printf(G"\t\t\t1. split_array[%d]: %s\n"RS, j, split_array[j]);
	// 	if (expand_token_env_1(data, index_token) == -1)
	// 		return (NULL);
	// 	else if (expand_token_env_2(data, env, index_token) == -1)
	// 		return (NULL);
	// 	j++;
	// }
	/* memo */

	// while (split_array[i] != NULL)
	// {
	// 	if (res == NULL)
	// 	{
	// 		printf(P"\t\t\t\tStart: split_array[%d]: %s\n"RS, i, split_array[i]);
	// 		res = strdup(split_array[i]);	// Cpy first TOKEN
	// 		printf(P"\t\t\t\tres: %s\n"RS, res);
	// 	}
	// 	else
	// 	{
	// 		tmp = strdup(res);	// cpy 'res' to 'tmp'
	// 		free(res);
	// 		printf(RED"\t\t\t\tWihle: split_array[%d]: %s\n"RS, i, split_array[i]);
	// 		res = ft_strjoin(tmp, split_array[i]);
	// 		printf(RED"\t\t\t\tres: %s\n"RS, res);
	// 		free(tmp);
	// 	}
	// 	i++;
	// }
	for (int k = 0; split_array[k] != NULL; k++)
		free(split_array[k]);
	free(split_array);
	return (res);
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
	data.n_word = count_word(data.str, 0, 0, 0, data);


	/* memo */
	printf(RED"\n\tn_word: %d\n"RS, data.n_word);
	printf(RED"\tn_sq: %d\n\tn_dq: %d\n\n"RS, data.n_sq, data.n_dq);
	/* memo */


	if (data.n_word == 0)
		return (NULL);
	data.token = malloc((data.n_word + 1) * sizeof(char *));
	if (data.token == NULL)
		return (NULL);
	if (ft_chopper(&data, data.str, 0) == -1)
		return (NULL);


	/* memo */
	int i = 0;
	printf(G"\tBEFORE(original)\n"RS);
	while (i < data.n_word)
	{
		printf("\tdata.token[%d]: "G"%s"RS"\n", i, data.token[i]);
		i++;
	}
	/* memo */

	/* memo */
	printf(P"\n\tSTART(expanding)\n"RS);
	/* memo */


	if (expand_env(&data, env, 0) == -1)
		return (NULL);


	/* memo */
	printf(G"\n\tFINISH(expanding)\n"RS);
	i = 0;
	while (i < data.n_word)
	{
		printf("\tdata.token[%d]: "G"%s"RS"\n", i, data.token[i]);
		i++;
	}
	/* memo */


	return (data.token);
}

/*
	[ NOT DELETE YET ]
	if (data.n_sq + data.n_dq > 0)
		if (check_quote_order(data.str, &data, 0, 0) == -1)
			return (NULL);

	int n_sq = data.n_sq;
	int n_dq = data.n_dq;
	printf("n_sq: %d, n_dq: %d\n", n_sq, n_dq);

	------------------------------------------------------------

	[ NOT USED ]
	data.str = omit_pair_quotes_from_string1(user_input);
	data.str = omit_pair_quotes_from_string2(data.str);

	char	*omit_pair_quotes_from_string1(char *input)
	{
		int		i;
		int		output_index;
		int		quote_count;
		int		length_input;
		char	*result;

		i = -1;
		output_index = 0;
		quote_count = 0;
		length_input = ft_strlen(input);
		result = (char *)malloc(length_input + 1);
		while (++i < length_input)
		{
			if (input[i] == '\"')
			{
				quote_count++;
				if (quote_count % 2 == 0)
					continue ;
			}
			else
				result[output_index++] = input[i];
		}
		result[output_index] = '\0';
		return (result);
	}

	------------------------------------------------------------

	char	*omit_pair_quotes_from_string2(char *input)
	{
		int		i;
		int		output_index;
		int		quote_count;
		int		length_input;
		char	*result;

		i = -1;
		output_index = 0;
		quote_count = 0;
		length_input = ft_strlen(input);
		result = (char *)malloc(length_input + 1);
		while (++i < length_input)
		{
			if (input[i] == '\'')
			{
				quote_count++;
				if (quote_count % 2 == 0)
					continue ;
			}
			else
				result[output_index++] = input[i];
		}
		result[output_index] = '\0';
		return (result);
	}

	------------------------------------------------------------

	i = 0;
	printf(RED"\n\tDelete_single_quote\n"RS);
	while (i < data.n_word)
	{
		data.token[i] = delete_sq(data.token[i]);
		printf("\tdata.token[%d]: "G"%s"RS"\n", i, data.token[i]);
		i++;
	}

	i = 0;
	printf(RED"\n\tDelete_double_quote\n"RS);
	while (i < data.n_word)
	{
		data.token[i] = delete_dq(data.token[i]);
		printf("\tdata.token[%d]: "G"%s"RS"\n", i, data.token[i]);
		i++;
	}
*/