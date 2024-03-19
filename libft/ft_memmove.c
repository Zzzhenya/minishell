/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:48:35 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 12:11:00 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (src == dst || n == 0)
		return (d);
	if (d > s)
		while (n--)
			d[n] = s[n];
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (d);
}

/*
int	main(void)
{
	char	str1[] = "ABCDEFGHI";
	char	str2[] = "123456789";

	printf("before: %s\n", str1);
	ft_memmove(str1 + 2, str1, 3);
	printf("after: %s\n", str1);
	printf("before: %s\n", str2);
	ft_memmove(str2, str2 + 2, 3);
	printf("after: %s\n", str2);
	return (0);
}
*/
