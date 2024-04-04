/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:48:29 by tkwak             #+#    #+#             */
/*   Updated: 2023/09/06 15:01:15 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countrow(char const *s, char c)
{
	char	prvc;
	int		index;
	int		row;

	row = 0;
	index = 0;
	prvc = 0;
	if (s[index] != c && s[index] != 0)
		row++;
	while (s[index])
	{
		if (prvc == c && s[index] != c)
			row++;
		prvc = s[index];
		index++;
	}
	if (c == 0)
		row = row - 1;
	return (row);
}

int	tool4free(char **str, int i4str)
{
	if (str[i4str] == NULL)
	{
		while (i4str >= 0)
			free(str[i4str --]);
		free(str);
		return (-1);
	}
	return (1);
}

char	**linebyline(char **str, char const *s, char c)
{
	int	i;
	int	i4str;
	int	start;

	i = 0;
	i4str = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			str[i4str] = ft_substr(s, start, i - start);
			if (tool4free(str, i4str) < 0)
				return (NULL);
			i4str++;
		}
		else
			i++;
	}
	str[i4str] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		row;

	row = countrow(s, c);
	str = (char **)malloc((row + 1) * sizeof(char *));
	if (!str || !s)
		return (NULL);
	str = linebyline(str, s, c);
	if (str == NULL)
	{
		free (str);
		return (NULL);
	}
	return (str);
}

/*
char	**linebyline(char **str, char const *s, char c)
{
	int	i;
	int	i4str;
	int	start;

	i = 0;
	i4str = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			str[i4str] = ft_substr(s, start, i - start);
			if (str[i4str] == NULL)
			{
				tool4free(str, i4str);
				return (NULL);
			}
			i4str++;
		}
		else
			i++;
	}
	str[i4str] = NULL;
	return (str);
}
*/