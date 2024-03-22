/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:39:50 by sde-silv          #+#    #+#             */
/*   Updated: 2023/10/25 13:45:53 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		n;
	int		sign;

	i = 0;
	sign = 1;
	n = 0;
	while (nptr[i] && ft_isspace(nptr[i]) != 0)
		i ++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i ++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i] - 48);
		i ++;
	}
	return (sign * n);
}
/*
int	main(void)
{
	char	*str;

	str = "+47";
	ft_putnbr_fd(atoi((const char *)str), 1);
	write (1, "\n", 1);
	ft_putnbr_fd(ft_atoi((const char *)str), 1);
	write (1, "\n", 1);
	return (0);
}
*/
