/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_skip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:03:01 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/27 20:03:09 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* [F]
    If meet with space -> return (1)
*/
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n')
		return (-1);
	if (c == '\v' || c == '\t')
		return (-1);
	if (c == '\f' || c == '\r')
		return (-1);
	return (0);
}

/* [F]
	skip normal character on the string.
*/
void	skip_normal_char(char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '='
		&& str[*i] != '\"' && str[*i] != '\''
		&& str[*i] != '<' && str[*i] != '>' && str[*i] != '|'
		&& str[*i] != '\n' && str[*i] != '\v' && str[*i] != '\t'
		&& str[*i] != '\f' && str[*i] != '\r')
		*i += 1;
}

/* [F]
	skip ' 'space in str
*/
void	skip_space_in_str(char *str, int *i)
{
	while (ft_isspace(str[*i]) == -1)
		*i += 1;
	return ;
}

/*	[F]
	Put the (c & '\0') to the end of the string.
*/
char	*strjoin_c(char *str, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = 0;
	return (res);
}

/*	[F]
	Same as strjoin_c // param: str, c
	Difference: // param: str, str
*/
char	*strrjoin(char *s1, char *s2)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1)
		return (s2);
	else
	{
		while (s2 && s2[i])
		{
			res = strjoin_c(s1, s2[i]);
			i++;
		}
	}
	return (res);
}
