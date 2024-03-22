/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:38:24 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/12 16:18:41 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	include ft_putendl_fd.c when testing main
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j ++;
		}
		i ++;
	}
	return (NULL);
}
/*
int main(void)
{
	char	*ptr;

	ptr = ft_strnstr("Hello World!", "l", 0);
	if (ptr)
		ft_putendl_fd(ptr, 1);
	ptr = ft_strnstr("Hello World!", "l", 1);
	if (ptr)
        ft_putendl_fd(ptr, 1);
	ptr = ft_strnstr("Hello World!", "l", 2);
	if (ptr)
        ft_putendl_fd(ptr, 1);
	ptr = ft_strnstr("Hello World!", "l", 11);
	if (ptr)
        ft_putendl_fd(ptr, 1);
	ptr = ft_strnstr("Hello World!", "l", 12);
	if (ptr)
        ft_putendl_fd(ptr, 1);
	ptr = ft_strnstr("Hello World!", "l", 15);
	if (ptr)
        ft_putendl_fd(ptr, 1);
	ptr = ft_strnstr("", "l", 3);
	if (ptr)
        ft_putendl_fd(ptr, 1);
	ptr = ft_strnstr("Hello World!", "", 15);
	if (ptr)
        ft_putendl_fd(ptr, 1);
	ptr = ft_strnstr("Hello World!", "l", -1);
	if (ptr)
        ft_putendl_fd(ptr, 1);
	ptr = ft_strnstr("Hello World!", "l", -200);
	if (ptr)
        ft_putendl_fd(ptr, 1);
	else
		ft_putendl_fd("Function returned NULL", 1);
	return (0);
}
*/
