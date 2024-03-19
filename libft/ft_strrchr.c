/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:47:36 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 14:41:05 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*result;

	i = 0;
	result = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			result = (char *)&str[i];
		i++;
	}
	if ((unsigned char)c == 0)
		result = (char *)&str[ft_strlen(str)];
	return (result);
}

/*
int	main(void)
{
	char	*str;

	str = "dasdasdhknpvhono";
	printf("%s\n", ft_strchr(str, 'h'));
	return (0);
}
*/
