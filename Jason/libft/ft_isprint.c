/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:18:51 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 12:09:02 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*
int	main(void)
{
	int		i;
	char	*str;

	str[] = "abced\n\r\t\bd";
	i = 0;
	while (i < 10)
	{
		printf("%d\n", ft_isprint(str[i]));
		i++;
	}
	return (0);
}
*/
