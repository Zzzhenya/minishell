/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:49:29 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 12:33:37 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This function erases the data in the 'n' bytes of the memory starting at the
** location pointed by 's', writing zeroes.
** For further information, please check the Standard C Library function
** bzero(void *s, size_t n)i
** s가 가리키는 곳에 '0'바이트를 n개만큼 적음.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*convert;

	i = 0;
	convert = (unsigned char *)s;
	while (i < n)
	{
		convert[i] = 0;
		i++;
	}
}

// why do we have to change the format of (void *s) to (unsigned char *) ??
// char == here one by one is converted by 0.
// instead of char, using int happend a error.
// char is the only variable to deal with each one byte.
// but still don't know about why unsigned....
