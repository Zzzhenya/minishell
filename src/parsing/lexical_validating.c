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

void	toggle_inword_inquote(int *flag_inword, int *n_word, int *flag_inquote)
{
	if (*flag_inquote == 1)
	{
		*n_word += 1;
		*flag_inword = 0;
		*flag_inquote = 0;
	}
	else
	{
		*flag_inword = 1;
		*flag_inquote = 1;
	}
	return ;
}

/*
	Count word when the char is;
		<
		>
		|
		$

*/

int	count_word(const char *str, int n_word, int inword, int inquote)
{
	char prev;
	while (*str)
	{
		if (*str == ' ' && inquote == 0)
			inword = 0;
		else if (*str == '<' || *str == '>' || *str == '|')
		{
			n_word ++;
			inword = 0;
		}
		else if (*str == '"' || *str == '\'')
		{
			if (inquote == 1)
			{
				n_word ++;
				inword = 0;
				inquote = 0;
				prev = 0;
			}
			else if (prev == *str)
			{
				prev = *str;
				inquote = 1;
				inword = 1;
			}
		}
		else
		{
			if (inword == 0)
			{
				n_word ++;
				inword = 1;
			}
		}							
		str ++;
	}
	return (n_word);
}

/*	Add function for delete ""	*/
/*
char	*omit_pair_quotes_from_string(char *input)
{
	int		i;
	int		output_index;
	int		quote_count;
	int		length_input;
	char	*result;

	printf("1.\n");
	i = 0;
	output_index = 0;
	quote_count = 0;
	length_input = strlen(input);
	result = (char *)malloc(length_input + 1);
	while (i < length_input)
	{
		if (input[i] == '\"')
		{
			printf("2. input[%d]\n", i);
			quote_count++;
			if (quote_count % 2 == 0)
				continue ;
		}
		result[output_index++] = input[i];
		i++;
	}
	printf("3. result: %s\n", result);
	result[output_index] = '\0';
	return (result);
}
*/
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
	length_input = strlen(input);
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
	length_input = strlen(input);
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

char	**validate_input(char *user_input, char **env)
{
	t_data	data;

	data.str = user_input;
	if (count_quote(user_input, &data) == -1)
	{
		printf("Syntax error\n");
		return (NULL);
	}
	// Commented out. if quotes are omitted before word split, cannot differenciate word spaces 
		//from spaces within strings
	// data.str = omit_pair_quotes_from_string1(user_input);
	// data.str = omit_pair_quotes_from_string2(data.str);
	data.n_word = count_word(data.str, 0, 0, 0);
	printf("n_word: %d\n", data.n_word);
	if (data.n_word == 0)
		return (NULL);
	if (data.n_sq + data.n_dq > 0)
		if (check_quote_order(data.str, &data, 0, 0) == -1)
			return (NULL);
	data.token = malloc((data.n_word + 1) * sizeof(char *));
	if (data.token == NULL)
		return (NULL);
	if (ft_chopper(&data, data.str, 0) == -1)
		return (NULL);
	if (expand_env(&data, env, 0) == -1)
		return (NULL);
	/* memo */
	// int i = 0;
	// while (i < data.n_word)
	// {
	// 	printf("\n\t3. data.token[%d]: %s", i, data.token[i]);
	// 	i++;
	// }
	// printf("\n");
	/* memo */
	return (data.token);
}

// #include "../../include/minishell.h"

// void	toggle_inword_inquote(int *flag_inword, int *n_word, int *flag_inquote)
// {
// 	if (*flag_inquote == 1)
// 	{
// 		*n_word += 1;
// 		*flag_inword = 0;
// 		*flag_inquote = 0;
// 	}
// 	else
// 	{
// 		*flag_inword = 1;
// 		*flag_inquote = 1;
// 	}
// 	return ;
// }

// int	count_word(const char *str, int n_word, int flag_inword, int flag_inquote)
// {
// 	while (*str)
// 	{
// 		if (*str == ' ' && flag_inquote == 0)
// 			flag_inword = 0;
// 		else if (*str == '<' || *str == '>'
// 			|| *str == '|' || *str == '$')
// 		{
// 			n_word++;
// 			flag_inword = 0;
// 		}
// 		else if (*str == '"' || *str == '\'')
// 			toggle_inword_inquote(&flag_inword, &n_word, &flag_inquote);
// 		else
// 		{
// 			if (flag_inword == 0)
// 			{
// 				n_word++;
// 				flag_inword = 1;
// 			}
// 		}
// 		str++;
// 	}
// 	return (n_word);
// }

// char	**validate_input(char *user_input, char **env)
// {
// 	t_data	data;

// 	data.str = user_input;
// 	if (count_quote(user_input, &data) == -1)
// 		return (NULL);
// 	data.n_word = count_word(data.str, 0, 0, 0);
// 	// printf("data.n_word: %d\n", data.n_word);
// 	if (data.n_word == 0)
// 		return (NULL);
// 	if (data.n_sq + data.n_dq > 0)
// 		if (check_quote_order(user_input, &data, 0, 0) == -1)
// 			return (NULL);
// 	data.token = malloc((data.n_word + 1) * sizeof(char *));
// 	if (data.token == NULL)
// 		return (NULL);
// 	if (ft_chopper(&data, user_input, 0) == -1)
// 		return (NULL);
// 	if (expand_env(&data, env, 0) == -1)
// 		return (NULL);
// 	/*int i = 0;
// 	while (i < data.n_word)
// 	{
// 		printf("data.token: %s\n", data.token[i]);
// 		i++;
// 	}*/
// 	return (data.token);
// }