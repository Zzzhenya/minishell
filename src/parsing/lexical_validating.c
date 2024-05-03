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
	printf("2.n_dq: %d, n_sq: %d\n", data.n_dq, data.n_sq);

	int	cpy_n_sq = data.n_sq;
	int	cpy_n_dq = data.n_dq;
	/* memo */
	printf(C"\n[1] How does 'USER_INPUT' consist?\n\n"RS);
	printf("\t*str	inquote	inword	prev_quote  n_word   cpy_n_sq   cpy_n_dq\n");
	printf("\t%c	   %d	   %d	   %c	     %d		%d	  %d\n\n", *str, inquote, inword, prev, n_word, cpy_n_sq, cpy_n_dq);
	/* memo */

	while (*str)
	{
		if (*str == ' ' && inquote == 0)
		{
			printf(RED"Reset\n"RS);
			inword = 0;
		}
		else if ((*str == '<' || *str == '>' || *str == '|') && inquote == 0)
		{
			n_word++;
			inword = 0;
		}
		else if (*str == '\"' || *str == '\'')
		{
			if (inquote == 1) // Already in 'quote' // ' ' ' '
			{
				printf(G"IN QUOTE\n"RS);
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
					printf(G"Prev quote type = curr quote type\n"RS);
					if (*str == '\"')
					{
						if (*(str + 1) == ' ' && (cpy_n_dq % 2 != 0))
						{
							printf(RED"Reset everything, cause quote is pair and next is 'space'\n"RS);
							inword = 0;
							inquote = 0;
							prev = 0;
						}
						else if (ft_isalpha(*(str + 1)))
						{
							printf("Next char is alphabet\n");
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
						//if (prev != '\'' || prev != 0)
						// cpy_n_dq--;
						// if (prev != '\'')
						// 	cpy_n_dq--;
					}
					else // *str == \'
					{
						printf("111\n");
						if (*(str + 1) == ' ' && (cpy_n_sq % 2 != 0))
						{
							printf(RED"Reset everything, cause quote is pair and next is 'space'\n"RS);
							inword = 0;
							inquote = 0;
							prev = 0;
							cpy_n_sq--;
						}
						else if (ft_isalpha(*(str + 1)))
						{
							printf("Next char is alphabet\n");
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
							if (prev != '\"')
								cpy_n_sq--;
							//if (prev != '\"' || prev != 0)
							//cpy_n_sq--;
						}
					}
				}
			}
			else // Not in quote: inquote == 0, start in 'quote' (' or ")
			{
				printf(RED"NOT IN QUOTE YET\n"RS);
				// if (prev != *str) // Not stored any other ' or "
				// {
					// if (prev == 0)
					// {
				prev = *str; // save ' or " for prev
				if (*str == '\'')
				{
					printf(G"START SINGLE QUOTE\n"RS);
					if (inword == 0)
						n_word++;
					cpy_n_sq--;
					// if (cpy_n_sq == 0)
					// {
					// 	printf("ss\n");
					// 	n_word++;
					// }
				}
				else if (*str == '\"')
				{
					printf(G"START DOUBLE QUOTE\n"RS);
					if (inword == 0)
						n_word++;
					cpy_n_dq--;
					// if (cpy_n_dq == 0)
					// 	n_word++;
				}
					// }
				inquote = 1;
				inword = 1;
				// }
				// else
				// {
				// 	printf(C"1111\n"RS);
				// 	n_word++;
				// 	inword = 0;
				// 	inquote = 0;
				// 	prev = 0;
				// }
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
		printf("\t%c	   %d	   %d	   %c	     %d		%d	  %d\n", *str, inquote, inword, prev, n_word, cpy_n_sq, cpy_n_dq);
		printf("-------------------------------------------------------------------------\n");
		str++;
	}
	return (n_word);
}

int	count_backslash(const char *input)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	// printf("Success to call the [f] count_backslashes.\n");
	while (input[i] != '\0')
	{
		// printf("input[%d]: %c\n", i, input[i]);
		if (input[i] == '\\')
			res++;
		// printf("res: %d\n", res);
		i++;
	}
	return (res);
}

void	compress_backslash(char *input)
{
	int	i;
	int	j;
	int	consecutive_backslash;
	
	i = 0;
	j = 0;
	consecutive_backslash = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\\' && input[i + 1] == '\\')
			consecutive_backslash++;
		else
		{
			if (consecutive_backslash > 0)
			{
				if (consecutive_backslash % 2 != 0)
					input[j++] = '\\';
				consecutive_backslash = 0;
			}
			input[j++] = input[i++];
		}
		i++;
	}
	if (consecutive_backslash > 0 && consecutive_backslash % 2 != 0)
		input[j++] = '\\';
	input[j] = '\0';
}

/*
void	compress_backslash(char *input)
{
	int	i;
	int	j;
	int	origin_n_backslash;
	int	consecutive_backslash;
	int	final_n_backslash;
	
	i = 0;
	j = 0;
	origin_n_backslash = count_backslash(input);
	consecutive_backslash = 0;
	final_n_backslash = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\\' && input[i + 1] == '\\')
		{
			consecutive_backslash++;
			i++;
		}
		else
		{
			if (consecutive_backslash > 0)
			{
				input[j++] = '\\';
				consecutive_backslash = 0;
			}
			input[j++] = input[i++];
		}
	}
	input[j] = '\0';
	final_n_backslash = origin_n_backslash - consecutive_backslash;
	if (final_n_backslash % 2 != 0)
	{
		input[j - 1] = '\\';
		input[j] = '\0';
	}
}

void	compress_backslash(char *input)
{
	int i;
	int j;
	int	origin_n_backslash;
	int	final_n_backslash;
	
	i = 0;
	j = 0;
	origin_n_backslash = count_backslash(input);
	final_n_backslash = 0;
	if (origin_n_backslash % 2 == 0) // 백슬래시의 개수가 짝수일 경우에만 압축
	{
        final_n_backslash = origin_n_backslash / 2;
		while (input[i] != '\0')
		{
			if (input[i] == '\\' && input[i + 1] == '\\')
                i++;
			input[j] = input[i];
			i++;
			j++;
		}
        input[ft_strlen(input) - final_n_backslash] = '\0';
    }
	else
	{
		final_n_backslash = (origin_n_backslash - 1) / 2;
		while ()

	}
}
*/

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
	printf(RED"\tn_word: %d\n"RS, data.n_word);
	/* memo */

	if (data.n_word == 0)
		return (NULL);
	data.token = malloc((data.n_word + 1) * sizeof(char *));
	if (data.token == NULL)
		return (NULL);

	// /* memo */
	// printf("\n\tdata.str: %s$\n", data.str);
	// printf("\torignal_n_backslash: %d\n\n", count_backslash(data.str));
	// /* memo */

	// /* memo */
	// compress_backslash(data.str);
	// printf("\n\tAfter compress_data.str: %s$\n", data.str);
	// printf("\tfinal_n_backslash: %d\n\n", count_backslash(data.str));
	// /* memo */

	if (ft_chopper(&data, data.str, 0) == -1)
		return (NULL);
	if (expand_env(&data, env, 0) == -1)
		return (NULL);
	return (data.token);
}

/*	[Not used]

	if (data.n_sq + data.n_dq > 0)
		if (check_quote_order(data.str, &data, 0, 0) == -1)
			return (NULL);

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
*/