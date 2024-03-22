/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:59:37 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:46:20 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	ptr = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start ++;
	while (end + 1 > start && ft_strchr(set, s1[end]))
		end --;
	ptr = (char *)malloc(sizeof(char) * (end - start + 2));
	if (ptr)
		ft_strlcpy(ptr, (s1 + start), (end - start + 2));
	return (ptr);
}
/*
int	main(void)
{
	char *ptr;

	ptr = ft_strtrim("", "");
	write(1, ptr, ft_strlen(ptr));
	free (ptr);
	return (0);
}
*/
