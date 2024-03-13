/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:11:36 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 11:11:39 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/*	[F]
	Check the length of token, with using ft_strcmp.
*/
int	check_token_length(int *token)
{
	int	i;

	i = 0;
	while (token[i] != 0)
		i++;
	return (i);
}

/*	[F]
	Check the type of token, whether it is (redirection) or not
	4Types of redirections // < << > >>
*/
int	check_redirections(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (0);
	else if (ft_strcmp(str, ">") == 0)
		return (0);
	else if (ft_strcmp(str, ">>") == 0)
		return (0);
	else if (ft_strcmp(str, "<<") == 0)
		return (0);
	else
		return (1);
}

/*	[F]
	Check the type of token, with using ft_strcmp.
*/
int	check_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (T_PIPE);
	else if (check_redirections(str) == 0)
		return (T_REDIREC);
	else if (ft_strcmp(str, "\'") == 0)
		return (T_S_QUOTE);
	else if (ft_strcmp(str, "\"") == 0)
		return (T_D_QUOTE);
	else
		return (T_WORD);
}

/*	[F]
	count rows from 2d_array
*/
int	count_row_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

/*	[F]
	[Param]
	param(1) token_malloc(validated_token);
			= char **validated_token
			= The rsult of the 2D-array after chopping.

	[Progress]
	1. Count tokens (n_token)
	2. Allocate memory for token (+1: NULL for last digit)
	3. Check the type of token and copy it to res[i]
	4. Return (*res)
*/
int	*token_malloc(char **after_chopping)
{
	int	i;
	int	n_token;
	int	*res;

	i = 0;
	n_token = count_row_2d_array(after_chopping);
	res = (int *)malloc(sizeof(int) * (n_token + 1));
	while (i < n_token)
	{
		res[i] = check_token_type(after_chopping[i]);
		i++;
	}
	res[i] = T_NULL;
	return (res);
}
