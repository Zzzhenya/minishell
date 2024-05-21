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

static void	setup_checks(t_parse *checks, t_data data)
{
	checks->n_word = 0;
	checks->inword = 0;
	checks->inquote = 0;
	checks->cpy_n_sq = data.n_sq;
	checks->cpy_n_dq = data.n_dq;
	checks->prev = 0;
}

int	count_word(const char *str, t_data data)
{
	t_parse	checks;

	setup_checks(&checks, data);
	while (*str)
	{
		if (*str == ' ' && checks.inquote == 0)
			checks.inword = 0;
		else if ((*str == '<' || *str == '>' || *str == '|')
			&& checks.inquote == 0)
		{
			if (ct_wd_rdr_pipe(&checks, str) == 0)
				return (0);
		}
		else if (*str == '\"' || *str == '\'')
		{
			if (checks.inquote == 1)
				ct_wd_inquote(&checks, str);
			else
				ct_wd_outquote(&checks, str);
		}
		else
			ct_wd_else(&checks);
		str++;
	}
	return (checks.n_word);
}

char	*ft_cpy_str(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_temp_array(char **split_array)
{
	int	j;

	j = 0;
	while (split_array[j] != NULL)
	{
		free(split_array[j]);
		j++;
	}
	free(split_array);
}

/*
	[ For checking ]
	printf(RED"\tn_word: %d\n"RS, data.n_word);
	for (int k = 0; k < data.n_word; k++)
		printf(P"\t\tdata.token[%d]: %s\n"RS, k, data.token[k]);

	[ Delete ]
	(void)env;
*/

int	add_char_to_end(t_data *data, int i, int j)
{
	char *new;

	new = NULL;
	new = malloc(sizeof(char) * data->token[i][j])
}

void	expand_and_remove_quotes(t_data *data, char **env)
{
	int i = 0;
	int j = 0;

	while (data->token[i] != NULL)
	{
		j = 0;
		while (data->token[i][j] != '\0')
		{
			// if (data->token[i][j] == '$')
			// 	j += check_for_env_var(data, i, j, env);
			// else
				j += add_char_to_end(data, i, j);
		}
		add_null_to_end(data, i, j);
		i++;
	}
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
	data.n_word = count_word(data.str, data);
	if (data.n_word == 0)
		return (NULL);
	data.token = NULL;
	data.token = malloc((data.n_word + 1) * sizeof(char *));
	if (data.token == NULL)
		return (NULL);
	if (ft_chopper(&data, data.str, 0, 0) == -1)
		return (NULL);
	expand_and_remove_quotes(&data, env);
	// if (expand_env(&data, env, 0, 0) == -1)
	// 	return (NULL);
	return (data.token);
}
