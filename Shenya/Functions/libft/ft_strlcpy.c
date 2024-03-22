/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:56:16 by sde-silv          #+#    #+#             */
/*   Updated: 2023/10/04 14:01:45 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
*/

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i] != '\0')
			i ++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i ++;
	}
	if (i < size)
		dest [i] = '\0';
	while (src[i] != '\0')
		i ++;
	return (i);
}
/*
int	main(void)
{
	char	src[10] = "Hello";
	char	dest[10] = "AAAAAAAAA";
	int		size;

	write (1, src, 10);
	write (1, "\n", 1);
	write (1, dest, 10);
	write (1, "\n", 1);
	size = ft_strlcpy(dest, src, 5);
	write (1, src, 10);
	write (1, "\n", 1);
	write (1, dest, size);
	write (1, "\n", 1);
	return (0);
}
*/
