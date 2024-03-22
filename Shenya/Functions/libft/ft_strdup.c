/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:20:56 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 15:03:20 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
*/

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, ft_strlen(s) + 1);
	return (ptr);
}
/*
int	main(void)
{
	char	*ptr;
	char	*src;
	char	*ft_ptr;

	src = "Hello World";
	write (1, src, strlen(src));
	write (1, "\n", 1);

	ptr = strdup(src);
	write (1, ptr, strlen(src));
    write (1, "\n", 1);

	ft_ptr = ft_strdup(src);
    write (1, ft_ptr, strlen(src));
    write (1, "\n", 1);
	return (0);
}
*/
