/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:45:49 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:52:40 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
*/

char	*ft_strchr(const char *s, int c)
{
	while ((unsigned char)*s != (unsigned char)c && *s != '\0')
		s ++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
/*
int	main(void)
{
	write (1, strchr("HelloWor\nld!", 'd'), 5);
	write (1, ft_strchr("HelloWor\nld!", 'd'), 5);
	return (0);
}
*/
