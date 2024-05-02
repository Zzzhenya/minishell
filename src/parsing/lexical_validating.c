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

int	count_word(const char *str, int n_word, int inword, int inquote)
{
	char prev;

	prev = 0;

	/* memo */
	printf(C"\n[1] How does 'USER_INPUT' consist?\n\n"RS);
	printf("\t*str	inquote	inword	previous_quote\n");
	/* memo */

	while (*str)
	{
		if (*str == ' ' && inquote == 0)
			inword = 0;
		else if ((*str == '<' || *str == '>' || *str == '|') && inquote == 0)
		{
			n_word++;
			inword = 0;
		}
		else if (*str == '"' || *str == '\'')
		{
			if (inquote == 1)
			{
				if (prev != *str)
				{
					if (prev == 0)
						prev = *str;
					inquote = 1;
					inword = 1;
				}
				else
				{
					n_word++;
					inword = 0;
					inquote = 0;
					prev = 0;
				}
			}
			else
			{
				if (prev != *str)
				{
					if (prev == 0)
						prev = *str;
					inquote = 1;
					inword = 1;
				}
				else
				{
					n_word++;
					inword = 0;
					inquote = 0;
					prev = 0;
				}
			}
		}
		else
		{
			if (inword == 0)
			{
				n_word++;
				inword = 1;
			}
		}

		/* memo */
		printf("\t%c	   %d	   %d	   %c\n", *str, inquote, inword, prev);
		printf("\t----------------------------------------\n");
		/* memo */

		str++;
	}
	return (n_word);
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
	data.n_word = count_word(data.str, 0, 0, 0);

	/* memo */
	printf(RED"\tn_word: %d\n"RS, data.n_word);
	/* memo */

	if (data.n_word == 0)
		return (NULL);
	data.token = malloc((data.n_word + 1) * sizeof(char *));
	if (data.token == NULL)
		return (NULL);
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