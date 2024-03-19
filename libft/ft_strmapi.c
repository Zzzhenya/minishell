/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:25:59 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 12:16:07 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	index;
	unsigned int	len;

	res = NULL;
	index = 0;
	len = (unsigned int)(ft_strlen(s));
	if (s == NULL || f == NULL)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	while (s[index] != '\0' && index < len)
	{
		res[index] = f(index, s[index]);
		index++;
	}
	res[index] = '\0';
	return (res);
}
