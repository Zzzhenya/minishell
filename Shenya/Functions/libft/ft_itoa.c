/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:24:28 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 14:59:48 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <unistd.h>
	char *ft_itoa(int n);

n: 		the integer to convert.
Return: The string representing the integer.
		NULL if the allocation fails.
Des: 	Allocates (with malloc(3)) and returns a string
		representing the integer received as an argument.
		Negative numbers must be handled.

1. Count the (digits + "-" sign if available).
2. Malloc space for  digits + 1
3. Write '0\' to end
4. If negative convert to positive
5. Copy each digit to allocated memory in reverse 
6. Check for the sign in n and write it
7. include the case for n = -2147483648LL 
	(where n cannot be multiplied by -1)
*/

static int	count_digits(int n)
{
	int			count;
	long int	nb;

	count = 0;
	nb = n;
	if (nb <= 0)
	{
		count ++;
		nb = nb * -1;
	}
	while (nb)
	{
		nb = nb / 10;
		count ++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	int			digits;
	long int	nbr;

	digits = count_digits(n);
	nbr = n;
	ptr = malloc(sizeof(char) * digits + 1);
	if (!ptr)
		return (NULL);
	ptr[digits] = '\0';
	if (nbr < 0)
		nbr = nbr * -1;
	while (digits > 0)
	{
		digits --;
		ptr[digits] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		ptr[digits] = '-';
	return (ptr);
}
/*
int main(void)
{
	int i;

	i = 0;
	ft_putnbr_fd(i, 1);
	ft_putstr_fd("  : Int\n", 1);
	ft_putstr_fd(ft_itoa(i), 1);
	ft_putstr_fd("  : Str\n", 1);
	return (0);
}
*/
