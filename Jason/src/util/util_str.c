/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:03:15 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/27 20:03:17 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	[F]
	If "c" is !!!not!!! in "str"	->	return (-1)
	Else							->	return (i)
*/
int	ft_strchr_m(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

/*	[F]
	If compare s1 != s2	-> return (s1-s2)
	Else				-> return (0)
*/
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (*s1 - *s2);
	return (0);
}

/*	[F]
    For "echo" function.
	If "c" is not in "str"	->	return (-1)
	Else					->	return (i)
*/
int	ft_putstr_m(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}

/* [F]
    cpy (str) to data.token
*/
int	ft_strcpy_m1(t_data *data, char *str, int len, int j)
{
	int	i;
	int	index;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	data->token[j] = malloc((len + 1) * sizeof(char));
	if (!data->token[j])
		return (-1);
	index = 0;
	while (i < len)
	{
		data->token[j][index] = str[i];
		i++;
		index++;
	}
	data->token[j][index] = '\0';
	return (len);
}

/* [F]
    Same with (ft_strcpy_m1)
	But only use for normal character (!= |, >, <, ', "..)
*/
int	ft_strcpy_m2(t_data *data, char *str, int len, int j)
{
	int	i;
	int	index;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	data->token[j] = malloc((len + 1) * sizeof(char));
	if (!data->token[j])
		return (-1);
	index = 0;
	while (i < len && str[i] != ' ')
	{
		data->token[j][index] = str[i];
		i++;
		index++;
	}
	data->token[j][index] = '\0';
	return (len);
}
