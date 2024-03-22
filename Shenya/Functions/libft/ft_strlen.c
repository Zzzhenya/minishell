/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:38:23 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:54:36 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include<string.h>
#include<stdio.h>
*/

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len ++;
	return (len);
}
/*
int	main(void)
{
	printf ("strlen: %lu", strlen("A"));
	printf ("\nft_strlen: %lu \n", ft_strlen("A"));
	return (0);
}
*/
