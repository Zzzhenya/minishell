/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chopping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:57 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/23 15:19:46 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*case_s_quote(t_data *data, char *str, int i, int j)
{
	int	k;

	k = i;
	while (str[i] != '\'' && str[i] != '\0')
		i++;
	ft_strcpy_m1(data, str + k, i - k, j);
	return (str + i);
}

char	*case_d_quote(t_data *data, char *str, int i, int j)
{
	int	k;

	k = i;
	while (str[i] != '\"' && str[i] != '\0')
		i++;
	ft_strcpy_m1(data, str + k, i - k, j);
	return (str + i);
}

int	check_str_null(t_data *data, char *str, int i, int j)
{
	if (str[i] == '\0')
	{
		data->token[j] = NULL;
		return (-1);
	}
	return (0);
}

int	ft_chopper(t_data *data, char *str, int j)
{
	int	i;

	i = 0;
	if (str[0] == '\0' || str == NULL)
		return (-1);
	while (ft_isspace(str[i]) == -1)
		i++;
	if (check_str_null(data, str, i, j) == -1)
		return (0);
	skip_normal_char(str, &i);
	skip_space_in_str(str, &i);
	if (str[0] == '\'')
		str = case_s_quote(data, str, i + 1, j);
	else if (str[0] == '\"')
		str = case_d_quote(data, str, i + 1, j);
	else if (str[0] != '=' && str[0] != '\0'
		&& str[0] != '<' && str[0] != '>' && str[0] != '|')
		ft_strcpy_m2(data, str, i, j);
	else if ((str[0] == '>' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<'))
		i = ft_strcpy_m1(data, str, 2, j);
	else if (str[0] == '=' || str[0] == '<' || str[0] == '>' || str[0] == '|')
		i = ft_strcpy_m1(data, str, 1, j);
	if (ft_chopper(data, str + i, ++j) == -1 || str[i] == '\0')
		data->token[j] = NULL;
	return (0);
}
