/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:03:29 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 17:49:03 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1 || !set)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while ((start < end) && ft_strchr(set, s1[end - 1]))
		end--;
	result = (char *)malloc(1 * (end - start + 1));
	if (!result)
		return (0);
	ft_strlcpy(result, s1 + start, end - start + 1);
	return (result);
}
