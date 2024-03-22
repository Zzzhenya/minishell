/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:52:02 by sde-silv          #+#    #+#             */
/*   Updated: 2023/06/08 14:11:56 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <unistd.h>
s: 		The string from which to create the substring.
start: 	The start index of the substring in the string ’s’.
len:	The maximum length of the substring.

Return: The substring. OR NULL if the allocation fails.

Desc: Allocates (with malloc(3)) and returns a substring from the string ’s’. 
The substring begins at index ’start’ and is of maximum size ’len’.

strlen(s) < start
    ft_strdup("") : allocates sufficient memory for a copy of the string s1, does
     the copy, and returns a pointer to it.
strlen(s) >= start
	strlen(s + start) < len (s is the limiting factor)
		len = strlen(s + start)
	strlen(s + start) => len (len is the limiting factor)
Allocate mem (len + 1) of char size
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
/*
int    main(void)
{
    ft_substr("Hello World", 3, 5);
    return (0);
}
*/
