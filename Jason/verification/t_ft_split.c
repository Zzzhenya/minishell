/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:48:29 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/14 17:02:04 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_row(char const *s, char traget_c)
{
	int		i;
	int		row;
	char	previous_c;

	i = 0;
	row = 0;
	previous_c = '\0';
	if (!s[i])
		return (0);
	if (s[i] != traget_c && s[i])
		row++;
	while (s[i])
	{
		if (previous_c == traget_c && s[i] != traget_c)
			row++;
		previous_c = s[i];
		i++;
	}
	if (traget_c == '\0')
		row = row - 1;
	return (row);
}

int	free_2d(char **str, int i)
{
	if (str[i] == NULL)
	{
		while (i >= 0)
			free(str[i--]);
		free(str);
		return (-1);
	}
	return (1);
}

char	**linebyline(char **res, char const *s, char c)
{
	int	i;
	int	i_res;
	int	start;

	i = 0;
	i_res = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			res[i_res] = ft_substr(s, start, i - start);
			if (free_2d(res, i_res) < 0)
				return (NULL);
			i_res++;
		}
		else
			i++;
	}
	res[i_res] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		row;
	char	**res;

	if (s == NULL)
		return (NULL);
	row = count_row(s, c);
	res = (char **)malloc((row + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	res = linebyline(res, s, c);
	return (res);
}
