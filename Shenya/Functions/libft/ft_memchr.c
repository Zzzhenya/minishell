/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:52:35 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:39:08 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		ptr ++;
		i ++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*s;

	s = "Hello World!";
	write(1, memchr(s, 'W',strlen(s)), 6);
	write (1, "\n", 1);
	write(1, ft_memchr(s, 'W',strlen(s)), 6);
	write (1, "\n", 1);
			
}
*/
