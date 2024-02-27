/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_skip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:03:01 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/27 20:03:09 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* [F]
    If meet with space -> return (1)
*/
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n')
		return (-1);
	if (c == '\v' || c == '\t')
		return (-1);
	if (c == '\f' || c == '\r')
		return (-1);
	return (0);
}

/* [F]
	skip normal character on the string.
*/
void	skip_normal_char(char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '='
		&& str[*i] != '\"' && str[*i] != '\''
		&& str[*i] != '<' && str[*i] != '>' && str[*i] != '|'
		&& str[*i] != '\n' && str[*i] != '\v' && str[*i] != '\t'
		&& str[*i] != '\f' && str[*i] != '\r')
		*i += 1;
}

/* [F]
	skip ' 'space in str
*/
void	skip_space_in_str(char *str, int *i)
{
	while (ft_isspace(str[*i]) == -1)
		*i += 1;
	return ;
}
