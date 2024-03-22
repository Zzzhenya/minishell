/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:52:35 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:50:00 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] == ptr2[i])
			i ++;
		else
			return (ptr1[i] - ptr2[i]);
	}
	return (0);
}
/*
int	main(void)
{
	char	*s1;
	char	*s2;

	s1 = "Hello World!";
	s2 = "X";
	ft_putnbr_fd(memcmp((const void *)s1, (const void *)s2,strlen(s1)), 1);
	write (1, "\n", 1);
	ft_putnbr_fd(ft_memcmp((const void *)s1, (const void *)s2,strlen(s1)), 1);
	write (1, "\n", 1);
			
}
*/
