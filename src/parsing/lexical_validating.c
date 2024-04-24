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

int	count_word(const char *str, int n_word, int flag_inword, int flag_inquote)
{
	while (*str)
	{
		if (*str == ' ' && flag_inquote == 0)
			flag_inword = 0;
		else if (*str == '<' || *str == '>'
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

char	**validate_input(char *user_input, char **env)
{
	t_data	data;

	data.str = user_input;
	if (count_quote(user_input, &data) == -1)
		return (NULL);
	data.n_word = count_word(data.str, 0, 0, 0);
	// printf("data.n_word: %d\n", data.n_word);
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
	if (expand_env(&data, env, 0) == -1)
		return (NULL);
	/*int i = 0;
	while (i < data.n_word)
	{
		printf("data.token: %s\n", data.token[i]);
		i++;
	}*/
	return (data.token);
}
