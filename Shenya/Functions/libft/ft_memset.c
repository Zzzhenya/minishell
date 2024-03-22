/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:05:33 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:50:43 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include<string.h>
*/

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = (unsigned char)c;
		p ++;
		n --;
	}
	return (s);
}
/*
int	main(void)
{
	char arr[6] = "Hello";

//	write(1, memset(arr, 'A', 4), 5);	
	write(1, ft_memset(arr, 'A', 4), 5);
	return (0);
}
*/
