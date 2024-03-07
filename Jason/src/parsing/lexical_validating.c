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

/* [F]
//	change flags of word and quote, to count "words".
*/
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

/*	[F]
	[Main point]
	Count words

	[Form]
				      n_word   flag_inquote
	count_word(data.tmp, 0, 0, 0);
					  flag_inword

	[Starting value]
		data.tmp: user_input (ex) "ls -la | cat -e"
		count: 0
		flag_in_middle_word: 0
		= check if current pointer is inside word.
			현재 스트링을 가리키는 포인터가 "단어" 안에 있는지를 나타내는 플래그
		flag_in_middle_quotes: 0
		= check if current pointer is inside quotes.
			현재 스트링을 가리키는 포인터가 "쿼츠" 안에 있는지를 나타내는 플래그

	[Reason] Why not declare count and two flags inside of function
	= Answer: Line limit. Max: 25lines.

	[Progress]
	1. if: Case(1): meet with "space"(reference point for dividing word)
	2. else if: Case(2): meet with "redirection char"
	3. else if: Case(3): meet with "s_quote" or "d_quotes"
	4. else: Case(4): meet with "everything else"
*/
int	count_word(const char *str, int n_word, int flag_inword, int flag_inquote)
{
	while (*str)
	{
		if (*str == ' ' && flag_inquote == 0)
			flag_inword = 0;
		else if (*str == '=' || *str == '<' || *str == '>'
			|| *str == '|' || *str == '$')
		{
			n_word++;
			flag_inword = 0;
		}
		else if (*str == '"' || *str == '\'')
			toggle_inword_inquote(&flag_inword, &n_word, &flag_inquote);
		else
		{
			if (flag_inword == 0)
			{
				n_word++;
				flag_inword = 1;
			}
		}
		str++;
	}
	return (n_word);
}

/*
[main function for checking [f]count_word]
int	main(int ac, char **av)
{
	int	i = 0;
	int	count_words = 0;
	
	if (ac == 2)
	{
		count_words = count_word_num(av[1], 0, 0, 0);
		printf("count_words: %d\n", count_words);
		while (av[1][i])
		{
			printf("av[1][%d]: %c\n", i, av[1][i]);
			i++;
		}
	}
	return (0);
}
*/

/*	[F]
	[Progress]
	1. Cpy the pointer to "user_input" // (ex) "ls -l | cat -e"
	2. Count s_q & d_q from "user_input"
	3. If n_sq || n_dq isn't even number -> validate fails
	4. Count the number of "word" & save it in "data" struct
	5. If "n_sq" or "n_dq" is in case of one or more.
	6. Check the order of quotes and pair.
		If the order of quote doesn't have any problem, nothing change.
	7. Allocate memories for each word. token[0]: 1st word, token[1]: 2nd word ..
	8. Save all words to 2D-array in original order.
	9. Check ($) dollar sign and comparing with env variable

	[Return]
	Now we are storing each separate token that passed validation in (t_data data)
*/
char	**validate_input(char *user_input, char **env)
{
	t_data	data;

	data.str = user_input;
	if (count_quote(user_input, &data) == -1)
		return (NULL);
	data.n_word = count_word(data.str, 0, 0, 0);
	if (data.n_word == 0)
		return (NULL);
	if (data.n_sq + data.n_dq > 0)
		if (check_quote_order(user_input, &data, 0, 0) == -1)
			return (NULL);
	data.token = malloc((data.n_word + 1) * sizeof(char *));
	if (data.token == NULL)
		return (NULL);
	if (ft_chopper(&data, user_input, 0) == -1)
		return (NULL);
	if (expansion(&data, env, 0) == -1)
		return (NULL);
	return (data.token);
}

/*
[main function for checking [f]validate]
int	main(int ac, char **av, char **env)
{
	int	i = 0;
	char	*tmp;
	char	**array;
	if (ac && av)
	read_history("history_file");
	tmp = readline("promp> ");
	if ((array = validate_input(tmp, env)) == NULL)
	{
		printf("wrong input you goofy");
		return (0);
	}
	while (array[i] != NULL)
	{
		printf("<%s>\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}
*/
/*
int	main(void)
{
	char	*input;
	int		result;
	t_data	data;

	input = "  ls -l $$ | cat -e 'a  b'bc";
	data.n_word = count_word(input, 0, 0, 0);
	data.n_sq = 0;
	data.n_dq = 0;
	data.str = input;
	data.token = malloc(((data.n_word) + 1) * sizeof(char *));
	printf("\n\t 1. n_word: %d\n\n", data.n_word);
	if (!data.token)
	{
		printf("Fail to allocate memory\n");
		return (1);
	}
	result = ft_chopper(&data, input, 0);
	if (result != -1)
	{
		printf("\n\t 3. input: %s\n\n", input);
		for (int i = 0; data.token[i] != NULL; i++)
			printf("\t 4. data.token[%d]:%s\n", i, data.token[i]);
	}
	else
		printf("Error.\n");
	for (int i = 0; data.token[i] != NULL; i++)
		free(data.token[i]);
	free(data.token);
	return (0);
}
*/
