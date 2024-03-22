/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:08:37 by sde-silv          #+#    #+#             */
/*   Updated: 2023/08/28 15:09:52 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_ft_strlen(const char *s)
{
	size_t		len;

	len = 0;
	if (!s)
		return (len);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*gnl_ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (char)c && *s != '\0')
		s ++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*ptr;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len = gnl_ft_strlen(s1) + gnl_ft_strlen(s2);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
	{
		free(s1);
		return (NULL);
	}
	else
	{
		gnl_ft_strlcpy(ptr, s1, gnl_ft_strlen(s1) + 1);
		gnl_ft_strlcpy(ptr + gnl_ft_strlen(s1), s2, gnl_ft_strlen(s2) + 1);
		free(s1);
		return (ptr);
	}
}

size_t	gnl_ft_strlcpy(char *dest, char const *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dest || !src)
		return (i);
	if (size == 0)
	{
		while (src[i] != '\0')
			i ++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i ++;
	}
	if (i < size)
		dest [i] = '\0';
	while (src[i] != '\0')
		i ++;
	return (i);
}
