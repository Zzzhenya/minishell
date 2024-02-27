/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:43:54 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 12:16:26 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This function compares first 'n' bytes of 's1' and 's2' and return an integer
** lesser than, equal to, or greater than zero if 's1' is found, respectively,
** to be lesser than, to match, or be greater than s2.
** For further information, please check the Standard C Library function,
** 'strncmp(const char *s1, const char *s2, size_t n)'
*/

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < (n - 1))
		i++;
	if (str1[i] == str2[i])
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

/*
int	main(void)
{
	const char	*str1;
	const char	*str2;

	str1 = "abcde";
	str2 = "abcdf";
	printf("%d\n", ft_strncmp(str1, str2, 5));
}
*/

// format of return value is "int".
// char - char = char. but we can express it as an integer.
// Reason of unsigned char is, that there is no minus in character.
