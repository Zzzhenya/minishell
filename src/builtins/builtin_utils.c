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
	if (count <= 1)
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
