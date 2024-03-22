/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:38:23 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:49:08 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include<ctype.h>
#include<stdio.h>
*/

int	ft_isprint(int c)
{
	if (32 <= c && c <= 126)
		return (16384);
	return (0);
}
/*
int	main(void)
{
	printf ("isprint: %d", isprint(33));
	printf ("\nft_isprint: %d \n", ft_isprint(33));
	return (0);
}
*/
