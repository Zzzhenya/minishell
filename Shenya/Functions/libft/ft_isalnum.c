/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:38:23 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:36:45 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	include ft_isdigit when testing

#include<ctype.h>
#include<stdio.h>
*/

int	ft_isalnum(int c)
{
	if ('0' <= c && c <= '9')
		return (8);
	else if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (8);
	return (0);
}
/*
int	main(void)
{
	printf ("isalnum: %d", isalnum('A'));
	printf ("\nft_isalnum: %d \n", ft_isdigit('A'));
	return (0);
}
*/
