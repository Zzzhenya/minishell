/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:58:14 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:58:26 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char   *p;

	p = s;
	while (n > 0)
	{
		*p = (unsigned char)c;
		p ++;
		n --;
	}
	return (s);
}
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	byte_size;

	byte_size = nmemb * size;
	ptr = malloc(byte_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, byte_size);
	return (ptr);
}
