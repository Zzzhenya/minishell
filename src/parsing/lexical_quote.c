/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:05:45 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/19 16:14:56 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_quote(char *str, t_data *data)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote % 2 == 0)
			single_quote++;
		if (str[i] == '\"' && single_quote % 2 == 0)
			double_quote++;
		i++;
	}
	if (single_quote % 2 == 0 && double_quote % 2 == 0)
	{
		data->n_sq = single_quote;
		data->n_dq = double_quote;
		return (0);
	}
	return (-1);
}

char	*extract_quoted_string(char *str, int i)
{
	int		j;
	char	*res;

	j = 0;
	res = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] != '\'')
			res[j++] = str[i++];
		else if (str[i] == '\"' && str[i + 1] != '\"')
			res[j++] = str[i++];
		else
			i += 2;
	}
	res[j] = '\0';
	return (res);
}

int	check_quote_arrangement(char *str, int i)
{
	char	*m_str;

	m_str = extract_quoted_string(str, i);
	if (m_str == NULL)
		return (-1);
	if (ft_strlen(m_str) > 3 && m_str[0] == m_str[2] && m_str[0] != '\0')
	{
		free(m_str);
		return (-1);
	}
	if (check_unescaped_quote(m_str) == -1)
	{
		free(m_str);
		return (-1);
	}
	free(m_str);
	return (0);
}

int	check_unescaped_quote(char *str)
{
	if (str[0] != '\0')
	{
		if (check_quote_arrangement(str, 0) == -1)
		{
			free(str);
			return (-1);
		}
	}
	return (0);
}
/*
[ Original but the line is over 25, so i fixed it ]

int	check_quote_arrangement(char *str, int i)
{
	int		j;
	char	*m_str;

	j = 0;
	m_str = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (m_str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] != '\'')
			m_str[j++] = str[i++];
		else if (str[i] == '\"' && str[i + 1] != '\"')
			m_str[j++] = str[i++];
		else
			i += 2;
	}
	m_str[j] = '\0';
	if (ft_strlen(m_str) > 3 && m_str[0] == m_str[2] && m_str[0] != '\0')
	{
		free(m_str);
		return (-1);
	}
	if (check_unescaped_quote(m_str) == -1)
		return (-1);
	free(m_str);
	return (0);
}
*/
/*	[ Final ]
int	check_quote_order(char *user_input, t_data *data, int i, int k)
{
	char	*tmp_allocated_quote;

	tmp_allocated_quote = malloc((data->n_sq + data->n_dq + 1) * sizeof(char));
	if (tmp_allocated_quote == NULL)
		return (-1);
	while (user_input[i])
	{
		if (user_input[i] == '\'' || user_input[i] == '\"')
		{
			tmp_allocated_quote[k] = user_input[i];
			k++;
		}
		i++;
	}
	tmp_allocated_quote[k] = '\0';
	if (check_quote_arrangement(tmp_allocated_quote, 0) == -1)
	{
		printf("Fail: quote order\n");
		free(tmp_allocated_quote);
		return (-1);
	}
	free(tmp_allocated_quote);
	return (0);
}
*/
/*
[ Original but the line is over 25, so i fixed it ]

int	check_quote_order(char *user_input, t_data *data, int i, int k)
{
	char	*tmp_allocated_quote;

	tmp_allocated_quote = malloc((data->n_sq + data->n_dq + 1) * sizeof(char));
	if (tmp_allocated_quote == NULL)
		return (-1);
	while (user_input[i])
	{
		if (user_input[i] == '\'')
		{
			tmp_allocated_quote[k] = '\'';
			k++;
		}
		else if (user_input[i] == '\"')
		{
			tmp_allocated_quote[k] = '\"';
			k++;
		}
		i++;
	}
	tmp_allocated_quote[k] = '\0';
	if (check_quote_arrangement(tmp_allocated_quote, 0) == -1)
	{
		free(tmp_allocated_quote);
		return (-1);
	}
	free(tmp_allocated_quote);
	return (0);
}
*/
