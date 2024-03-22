/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:57:03 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:53:51 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;

	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	else
	{
		ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
		ft_strlcpy(ptr + ft_strlen(s1), s2, ft_strlen(s2) + 1);
		return (ptr);
	}
}
/*
int	main(void)
{
	write(1, ft_strjoin("Hello", " World"), 12);
	return (0);
}
*/
