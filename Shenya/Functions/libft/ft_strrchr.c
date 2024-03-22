/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:45:49 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 15:06:59 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len ++;
	return (len);
}
*/

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*ptr;

	ptr = (char *)s;
	len = ft_strlen(s);
	if (c == '\0')
		return (ptr + len);
	while (len != 0)
	{
		if (ptr[len] == (char)c)
			return (ptr + len);
		len --;
	}
	if (ptr[len] == (char)c)
		return (ptr);
	return (0);
}
/*
int	main(void)
{
	write (1, strrchr("HelloWorld!", 'o'), 2);
	write (1, "\n", 1);
	write (1, ft_strrchr("HelloWorld!", 'o'), 2);
	write (1, "\n", 1);
	return (0);
}
*/
