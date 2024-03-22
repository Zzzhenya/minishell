/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:07:49 by sde-silv          #+#    #+#             */
/*   Updated: 2023/08/28 15:08:01 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_from_file(int fd, char *carry)
{
	char	*ptr;
	int		bytes;

	bytes = 42;
	ptr = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!ptr)
		return (NULL);
	while (bytes != 0 && !gnl_ft_strchr(carry, '\n'))
	{
		bytes = read(fd, ptr, BUFFER_SIZE);
		if (bytes == -1)
		{
			free (carry);
			free (ptr);
			return (NULL);
		}
		ptr[bytes] = '\0';
		carry = gnl_ft_strjoin(carry, ptr);
	}
	free (ptr);
	return (carry);
}

static char	*gnl_get_line(char	*carry)
{
	int		i;
	char	*line;
	char	*lb;

	i = 0;
	if (carry[0] == '\0')
		return (NULL);
	lb = gnl_ft_strchr(carry, '\n');
	if (lb)
		i = ((lb - carry) / sizeof(char)) + 1;
	else
		i = gnl_ft_strlen(carry);
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
	{
		return (NULL);
	}
	gnl_ft_strlcpy(line, carry, i + 1);
	return (line);
}

static char	*gnl_get_carry(char	*carry)
{
	int		i;
	char	*temp;
	char	*lb;

	i = 0;
	if (!gnl_ft_strchr(carry, '\n'))
	{
		free (carry);
		return (NULL);
	}
	lb = gnl_ft_strchr(carry, '\n');
	i = gnl_ft_strlen(lb + 1) + 1;
	if (i == 1)
	{
		free(carry);
		return (NULL);
	}
	temp = malloc(sizeof(char) * i);
	if (!temp)
		return (NULL);
	gnl_ft_strlcpy(temp, lb + 1, i);
	free(carry);
	return (temp);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*carry[FD_MAX];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_MAX)
		return (NULL);
	carry[fd] = read_from_file(fd, carry[fd]);
	if (!carry[fd])
		return (NULL);
	line = gnl_get_line(carry[fd]);
	carry[fd] = gnl_get_carry(carry[fd]);
	return (line);
}
