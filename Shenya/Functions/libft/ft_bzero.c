/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:29:24 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:47:28 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = '\0';
		p ++;
		n --;
	}
}
/*
int	main(void)
{
	char	arr[12] = "Hello World";
	char	*p;

	p = arr + 3;
	write (1, arr, 12);
	write (1, "\n", 1);
	ft_bzero(p, 3);
	write (1, arr, 12);
	return (0);
}
*/
