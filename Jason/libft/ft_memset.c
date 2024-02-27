/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:48:23 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 12:11:31 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int val, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)dst)[i] = val;
		i++;
	}
	return (dst);
}

/*
int	main(void)
{
	char	*str;

	str = "abcedfg";
	printf("%s\n", (char *)ft_memset(str, 48, 3));
	return (0);
}
*/
