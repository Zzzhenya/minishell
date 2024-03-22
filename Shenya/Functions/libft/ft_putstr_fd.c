/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:40:04 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 15:02:53 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	ft_putstr_fd(char *s, int fd);

int	main(void)
{
	ft_putstr_fd("Hello World!", 1);
	return (0);
}
*/

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = 0;
	if (s)
	{
		len = gnl_ft_strlen(s);
		write (fd, s, len);
	}
}
