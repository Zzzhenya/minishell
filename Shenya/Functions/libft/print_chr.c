/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:08:25 by sde-silv          #+#    #+#             */
/*   Updated: 2023/07/12 17:08:27 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_chr(int next)
{
	unsigned char	c;

	c = (unsigned char)next;
	return (write (1, &c, sizeof(char)));
}
