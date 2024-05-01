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

int	check_str_null(t_data *data, char *str, int i, int j)
{
	if (str[i] == '\0')
	{
		data->token[j] = NULL;
		return (-1);
	}
	return (0);
}

char	*case_s_quote(t_data *data, char *str, int i, int j)
{
	int	k;

	k = i;
	while (str[i] != '\'' && str[i] != '\0')
		i++;
	ft_strcpy(data, str + k - 1, i + 1, j);
	i++;
	return (str + i);
}

char	*case_d_quote(t_data *data, char *str, int i, int j)
{
	int	k;

	k = i;
	while (str[i] != '\"' && str[i] != '\0')
		i++;
	ft_strcpy(data, str + k, i - 1, j);
	i++;
	return (str + i);
}

/*
char	*ifhelper(t_data *data, char *tmp, int i, int k)
{
 	int	m;

 	m = i;
 	while (tmp[i] != '\'' && tmp[i] != '\0')
 		i++;
 	ft_strcpy(data, tmp + m - 1, i + 1, k);
 	i++;
 	tmp = tmp + i;
 	return (tmp);
}

char	*elsehelper(t_data *data, char *tmp, int i, int k)
{
 	int	m;

 	m = i;
 	while (tmp[i] != '\"' && tmp[i] != '\0')
 		i++;
 	ft_strcpy(data, tmp + m, i - 1, k);
 	i++;
 	tmp = tmp + i;
 	return (tmp);
}
*/

/*

find start of word
find end of word
find length from start to end
copy the word to char *


*/

int	ft_chopper(t_data *data, char *str, int j)
{
	int	i;
	int start = 0;
	int end = 0;

	i = 0;
	while (str[i] == ' ')
		i ++;
	if (str[i] && str[i] != '\0')
		start = i;
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
	{
		i ++;
		end = i;
		*(data->token) = malloc(sizeof(char) * ((end - start) + 1))
		ft_strlcpy(*(data->token), &str[start], (end - start));
		*(data->token)++;
	}
	/*
	if (str[0] == '\0')
		return (-1);
	while (str[i] == ' ')
		str++;
	if (check_str_null(data, str, i, j) == -1)
		return (0);
	skip_normal_char(str, &i);
	if (str[0] == '\'')
		str = case_s_quote(data, str, i + 1, j);
	else if (str[0] == '\"')
		str = case_d_quote(data, str, i + 1, j);
	else if (str[0] != '\0'
		&& str[0] != '<' && str[0] != '>' && str[0] != '|')
		ft_strcpy(data, str, i, j);
	else if ((str[0] == '>' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<'))
		i = ft_strcpy(data, str, 2, j);
	else if (str[0] == '<' || str[0] == '>' || str[0] == '|')
		i = ft_strcpy(data, str, 1, j);
	if (ft_chopper(data, str + i, ++j) == -1 || str[i] == '\0')
		data->token[j] = NULL;
	return (0);*/
}

char	*get_pid_string(void)
{
	pid_t	pid;

	pid = getpid();
	return (ft_itoa((int)pid));
}

// void	handle_tokens(t_data *data, char *str, int *i, int j)
// {
// 	skip_normal_char(str, i);
// 	skip_space_in_str(str, i);
// 	if (str[0] == '\'')
// 		str = case_s_quote(data, str, *i + 1, j);
// 	else if (str[0] == '\"')
// 		str = case_d_quote(data, str, *i + 1, j);
// 	else if (str[0] != '=' && str[0] != '\0'
// 		&& str[0] != '<' && str[0] != '>' && str[0] != '|')
// 		ft_strcpy_m2(data, str, *i, j);
// 	else if ((str[0] == '>' && str[1] == '>')
// 		|| (str[0] == '<' && str[1] == '<'))
// 		*i = ft_strcpy_m1(data, str, 2, j);
// 	else if (str[0] == '=' || str[0] == '<' || str[0] == '>' || str[0] == '|')
// 		*i = ft_strcpy_m1(data, str, 1, j);
// }

// int	ft_chopper(t_data *data, char *str, int j)
// {
// 	int	i;

// 	i = 0;
// 	if (str[0] == '\0' || str == NULL)
// 		return (-1);
// 	while (ft_isspace(str[i]) == -1)
// 		i++;
// 	if (check_str_null(data, str, i, j) == -1)
// 		return (0);
// 	handle_tokens(data, str, &i, j);
// 	if (ft_chopper(data, str + i, ++j) == -1 || str[i] == '\0')
// 		data->token[j] = NULL;
// 	return (0);
// }
// [ Original but the line is over 25, so i fixed it ]
// int	ft_chopper(t_data *data, char *str, int j)
// {
// 	int	i;

// 	i = 0;
// 	if (str[0] == '\0')
// 		return (-1);
// 	while (str[i] == ' ')
// 		str++;
// 	if (check_str_null(data, str, i, j) == -1)
// 		return (0);
// 	skip_normal_char(str, &i);
// 	if (str[0] == '\'')
// 		str = case_s_quote(data, str, i + 1, j);

// 	else if (str[0] == '\"')
// 		str = case_d_quote(data, str, i + 1, j);
// 	else if (str[0] != '=' && str[0] != '\0'
// 		&& str[0] != '<' && str[0] != '>' && str[0] != '|')
// 		ft_strcpy_m2(data, str, i, j);
// 	else if ((str[0] == '>' && str[1] == '>')
// 		|| (str[0] == '<' && str[1] == '<'))
// 		i = ft_strcpy_m1(data, str, 2, j);
// 	else if (str[0] == '=' || str[0] == '<' || str[0] == '>' || str[0] == '|')
// 		i = ft_strcpy_m1(data, str, 1, j);
// 	if (ft_chopper(data, str + i, ++j) == -1 || str[i] == '\0')
// 		data->token[j] = NULL;
// 	return (0);
// }
