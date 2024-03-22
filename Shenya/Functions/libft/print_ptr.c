/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:04:46 by sde-silv          #+#    #+#             */
/*   Updated: 2023/07/12 18:18:04 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef __linux__

int	print_ptr(unsigned long int next, int format)
{
	int	digits;

	if (next == 0)
		return (print_str("(nil)"));
	else
	{
		digits = write (1, "0x", 2);
		return (digits + print_hex(next, format));
	}
}

#else

int	print_ptr(unsigned long int next, int format)
{
	int	digits;

	digits = write (1, "0x", 2);
	return (digits + print_hex(next, format));
}

#endif
