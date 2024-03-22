/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:42:26 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 15:04:24 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
#include <stdio.h>
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < size)
		i ++;
	while (src[j] != '\0' && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j ++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
int main(void)
{
	char	*src = "Worl";
	char	dst[15] = "Hello";

	printf("strlcat: %lu \n", strlcat(dst,src,0));
	printf("strlcat: %lu \n", ft_strlcat(dst,src,2));
	printf("strlcat: %lu \n", strlcat(dst,src,4));
	printf("strlcat: %lu \n", strlcat(dst,src,6));
	printf("strlcat: %lu \n", strlcat(dst,src,8));
	printf("strlcat: %lu \n", strlcat(dst,src,9));
	printf("strlcat: %lu \n", strlcat(dst,src,10));
	printf("strlcat: %lu \n", strlcat(dst,src,11));
	printf("strlcat: %lu \n", strlcat(dst,src,12));
	write(1, dst, 30);
	printf("\n strlen dst: %lu \n", strlen(dst));
	return (0);
}
*/
