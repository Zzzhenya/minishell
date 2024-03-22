/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:08:46 by sde-silv          #+#    #+#             */
/*   Updated: 2023/07/12 17:08:49 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_len(unsigned long int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static void	ft_put_hex(unsigned long int num, int format)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, format);
		ft_put_hex(num % 16, format);
	}
	else
	{
		if (num < 10)
			print_chr(num + '0');
		else
		{
			if (format == 'x' || format == 'p')
				print_chr(num - 10 + 'a');
			else if (format == 'X')
				print_chr(num - 10 + 'A');
		}
	}
}

int	print_hex(unsigned long int next, int format)
{
	unsigned long int	val;

	val = (unsigned long int)next;
	ft_put_hex(val, format);
	return (hex_len(val));
}
