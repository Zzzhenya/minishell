/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:00:03 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 11:56:31 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_len(int number)
{
	int	length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		length++;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

char	*ft_convert_int_to_str(int n, int length)
{
	long	number;
	char	*result;

	number = n;
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (NULL);
	if (number < 0)
	{
		result[0] = '-';
		number = -number;
	}
	if (number == 0)
		result[0] = '0';
	result[length--] = '\0';
	while (number != 0)
	{
		result[length] = number % 10 + '0';
		length--;
		number /= 10;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		length;
	char	*result;

	length = ft_get_len(n);
	result = ft_convert_int_to_str(n, length);
	return (result);
}
