/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:09:07 by sde-silv          #+#    #+#             */
/*   Updated: 2023/11/09 14:09:17 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Print the error message passed as a ponter to char
and exit with code EXIT_FAILURE */

void	ft_errexit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit (EXIT_FAILURE);
}
