/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:40:18 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 15:01:05 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*char_src;
	char	*char_dest;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	char_src = (char *)src;
	char_dest = (char *)dest;
	i = 0;
	while (i < n)
	{
		char_dest[i] = char_src[i];
		i ++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[12] = "Hello World!";
	char	dest[12];
	char	*rtn;
	int	n;

	n = 5;

	write (1,src, 12);
	write (1, "\n", 1);
	rtn = ft_memcpy(((void *)0), ((void *)0), 5);
	write(1,rtn, n);
	write (1, "\n", 1);	
	return (0);
}
*/