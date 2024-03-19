/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:44:11 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 16:39:08 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	if (dst_len >= size)
		return (src_len + size);
	while (dst_len + i < size - 1 && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/*
int	main(void)
{
	char	*dst;
	char	*src;

	dst = "goods";
	src = "saysomthing";
	printf("dst: %s\n", dst);
	printf("src: %s\n", src);
	printf("size: 9\n");
	printf("result: %zu, %s\n", ft_strlcat(dst, src, 9), dst);
}
*/
