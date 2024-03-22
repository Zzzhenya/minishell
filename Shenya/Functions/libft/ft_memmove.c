/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:58:56 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:39:51 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*char_s;
	char	*char_d;
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	char_s = (char *)src;
	char_d = (char *)dest;
	while (i < n)
	{
		if (dest < src)
		{
			char_d[i] = char_s[i];
			i ++;
		}
		else
		{
			char_d[n - 1] = char_s[n - 1];
			n --;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	dest[12];
	char    *src = "Hello World!";
	char    *rtn;
	int     n;

	n = 5;

	write (1,src, 12);
	write(1, "\n", 1);
	rtn = memmove(dest, src, n);
	write(1,rtn, n);
	write (1, "\n", 1);
	return (0);
}
*/
