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
	int	n_sq;
	int	n_dq;

	i = 0;
	n_sq = 0;
	n_dq = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			n_sq++;
		if (str[i] == '\"')
			n_dq++;
		i++;
	}
	if (n_sq % 2 == 0 && n_dq % 2 == 0)
	{
		data->n_sq = n_sq;
		data->n_dq = n_dq;
		return (n_sq);
	}
	return (-1);
}

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
