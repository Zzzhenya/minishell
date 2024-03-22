/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:29:51 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:45:14 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
#include <stdio.h>
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			i ++;
		else
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}
/*
int	main(int argc, char **argv)
{
	printf("strncmp: %i\n", strncmp(argv[1], argv[2], atoi(argv[3])));
	printf("ft_strncmp: %i\n", ft_strncmp(argv[1], argv[2], atoi(argv[3])));
	printf("nonASCII: %i\n", strncmp("\201", "", 1));
	printf("ft_nonASCII: %i\n", ft_strncmp("\201", "", 1));
	return (0);
}
*/
