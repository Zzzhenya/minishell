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

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 == *s2 && *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (*s1 - *s2);
	return (0);
}

int	ft_putstr_m(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}

int	ft_strcpy(t_data *data, char *tmp, int len, int k)
{
	int	i;

	i = 0;
	data->token[k] = malloc((len + 1) * sizeof(char));
	if (!data->token[k])
		return (-1);
	while (i < len)
	{
		data->token[k][i] = tmp[i];
		i++;
	}
	data->token[k][i] = '\0';
	return (len);
}