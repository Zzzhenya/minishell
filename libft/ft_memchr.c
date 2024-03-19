/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:48:43 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 12:10:02 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int v, size_t n)
{
	size_t			i;
	unsigned char	*ss;
	unsigned char	vv;

	i = 0;
	ss = (unsigned char *)src;
	vv = (unsigned char)v;
	while (i < n)
	{
		if (ss[i] == vv)
			return ((void *)(ss + i));
		i++;
	}
	return (0);
}

/*
int	main(void)
{
	char	*str;

	str = "abcedfg";
	printf("%s\n", (char *)ft_memchr(str, 99, 3));
	return (0);
}
*/

// S, V, N (source, value, number)
// search 'Value' in Source string until thte number.
// HOW
// 1. Casting: const void *src --> unsgined char *src
// 2. while (i < n), search
// 3. (if) find a 'v' in src --> return(src): address
// 4. (els) find nothing --> return(NULL)
