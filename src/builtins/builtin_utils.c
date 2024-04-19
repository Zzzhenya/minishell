/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:37:30 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/02 20:37:32 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*free_and_ret(char **arr)
{
	free (arr);
	arr = NULL;
	return (NULL);
}

static int	find_loc(char *str, int i, char c)
{
	int	loc;

	loc = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			loc = i;
			break ;
		}
		i ++;
	}
	return (loc);
}

char	**split_at_first_occ(char *str, char c, int i, int loc)
{
	char	**arr;

	arr = NULL;
	loc = find_loc(str, 0, c);
	arr = (char **)malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	arr[0] = malloc(sizeof(char) * loc + 1);
	if (!arr[0])
		return (free_and_ret(arr));
	ft_strlcpy(arr[0], str, loc + 1);
	if (loc + 1 == '\0')
		arr[1] = ft_strdup("");
	else
	{
		arr[1] = malloc(sizeof(char) * (ft_strlen(str) - loc));
		if (!arr[1])
			return (free_and_ret(arr));
		ft_strlcpy(arr[1], str + loc + 1, (ft_strlen(str) - loc));
	}
	arr[2] = NULL;
	return (arr);
}

/*
	Count the number of non-NULL but empty strings in
	the cmdstr array
*/
int	count_non_empty_strings(char **cmdstr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!cmdstr || !cmdstr[i])
		return (count);
	while (cmdstr[i] != NULL)
	{
		if (cmdstr[i][0] != '\0')
			count ++;
		i ++;
	}
	return (count);
}

/* 
	Remove non-NULL but empty strings from the 
	cmdstr array
*/
char	**strip_empty_strings(char **cmdstr)
{
	char	**arr;
	int		count;
	int		i;
	int		j;

	arr = NULL;
	i = 0;
	j = 0;
	count = count_non_empty_strings(cmdstr);
	if (count == 0)
		return (NULL);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	while (cmdstr[i] != NULL)
	{
		if (cmdstr[i][0] != '\0')
		{
			arr[j] = ft_strdup(cmdstr[i]);
			j ++;
		}
		i ++;
	}
	arr[j] = NULL;
	return (arr);
}
