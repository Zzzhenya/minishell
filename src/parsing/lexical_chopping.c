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

// void	check_sq(t_data *data, char **str, int *i, int *j)
// {
// 	if (*i != 0)
// 		*i = 0;
// 	case_s_quote(data, *str, *i, *j);
// }

// void	check_dq(t_data *data, char **str, int *i, int *j)
// {
// 	if (*i != 0)
// 		*i = 0;
// 	case_d_quote(data, *str, *i, *j);
// }

char	*check_sq(t_data *data, char **str, int *i, int *j)
{
	char	*res;

	res = NULL;
	if (*i != 0)
		*i = 0;
	res = case_s_quote(data, *str, *i, *j);
	return (res);
}

char	*check_dq(t_data *data, char **str, int *i, int *j)
{
	char	*res;

	res = NULL;
	if (*i != 0)
		*i = 0;
	res = case_d_quote(data, *str, *i, *j);
	return (res);
}

/*
	Current 'j' is 0 from the [f] validate_input.
		(ex) if (ft_chopper(&data, data.str, 0) == -1)

	[ Logic ]
	1. Inside inquote	-> cpy the space as a character to the token.
	2. Not Inside		-> Skip the space

	[ TEST ]
	P/F		string						n_word		Memory leaks
	[O]		' ' abc'a b'aa 'abc'			3			X
	[O] 	''aaa'    aa'aa''				1			X
	[O]		'abc' ababab'b'b				2			X
	[O]		abc's'a 'a'						2			X
	[O]		abc'ab' ddd'd'd					2			X
	[O]		'abc'aa aba ''a'a'				3			X
	[O] 	a a'a' a' a' a'a ' a' a '		5			X
	[O]		'' aa ''						3			X
*/
int	ft_chopper(t_data *data, char *str, int j, int i)
{
	i = 0;
	if (str[i] == '\0')
		return (-1);
	while (str[i] == ' ')
		str++;
	if (check_str_null(data, str, i, j) == -1)
		return (0);
	skip_normal_char(str, &i);
	if (str[i] != '\0' && str[i] == '\'')
		str = check_sq(data, &str, &i, &j);
	else if (str[i] != '\0' && (str[i] == '\"'))
		str = check_dq(data, &str, &i, &j);
	else if (str[0] != '\0' && str[0] != '<'
		&& str[0] != '>' && str[0] != '|')
		i = ft_strcpy(data, str, i, j);
	else if ((str[0] && str[1]) && ((str[0] == '>' && str[1] == '>')
			|| (str[0] == '<' && str[1] == '<')))
		i = ft_strcpy(data, str, 2, j);
	else if ((str[0]) && (str[0] == '<' || str[0] == '>' || str[0] == '|'))
		i = ft_strcpy(data, str, 1, j);
	if (ft_chopper(data, str + i, ++j, 0) == -1 || str[i] == '\0')
		data->token[j] = NULL;
	return (0);
}
/*
int	ft_chopper(t_data *data, char *str, int j, int i)
{
	if (str == NULL)
		return (-1);
	// if (str[i] == '\0')
	// 	return (-1);
	while (*str != '\0' && *str == ' ')
		str++;
	if (check_str_null(data, str, i, j) == -1)
		return (0);
	skip_normal_char(str, &i);
	if (str[i] != '\0' && str[i] == '\'')
		str = check_sq(data, &str, &i, &j);
	else if (str[i] != '\0' && (str[i] == '\"'))
		str = check_dq(data, &str, &i, &j);
	else if (str[0] != '\0' && str[0] != '<'
		&& str[0] != '>' && str[0] != '|')
		i = ft_strcpy(data, str, i, j);
	else if ((str[0] && str[1]) && ((str[0] == '>' && str[1] == '>')
			|| (str[0] == '<' && str[1] == '<')))
		i = ft_strcpy(data, str, 2, j);
	else if ((str[0]) && (str[0] == '<' || str[0] == '>' || str[0] == '|'))
		i = ft_strcpy(data, str, 1, j);
	if (ft_chopper(data, str + i, ++j, 0) == -1 || str[i] == '\0')
		data->token[j] = NULL;
	return (0);
}
*/
/*
int	ft_chopper(t_data *data, char *str, int j, int i)
{
	while (data->n_word > 0)
	{
		i = 0;
		while (*str != '\0' && *str == ' ')
			str++;
		if (check_str_null(data, str, i, j) == -1)
			return (0);
		skip_normal_char(str, &i);
		if (str[i] != '\0' && str[i] == '\'')
			str = check_sq(data, &str, &i, &j);
		else if (str[i] != '\0' && (str[i] == '\"'))
			str = check_dq(data, &str, &i, &j);
		else if (str[0] != '\0' && str[0] != '<'
			&& str[0] != '>' && str[0] != '|')
			i = ft_strcpy(data, str, i, j);
		else if ((str[0] && str[1]) && ((str[0] == '>' && str[1] == '>')
				|| (str[0] == '<' && str[1] == '<')))
			i = ft_strcpy(data, str, 2, j);
		else if ((str[0]) && (str[0] == '<' || str[0] == '>' || str[0] == '|'))
			i = ft_strcpy(data, str, 1, j);
		str += i;
		j++;
		data->n_word--;
	}
	data->token[j] = NULL;
	return (0);
}
*/
/*
int	ft_chopper(t_data *data, char *str, int j, int i)
{
	if (str == NULL || str[i] == '\0')
		return (-1);
	while (*str != '\0' && *str == ' ')
		str++;
	if (check_str_null(data, str, i, j) == -1)
		return (0);
	skip_normal_char(str, &i);
	if (str[i] != '\0' && str[i] == '\'')
		str = check_sq(data, &str, &i, &j);
	else if (str[i] != '\0' && (str[i] == '\"'))
		str = check_dq(data, &str, &i, &j);
	else if (str[0] != '\0' && str[0] != '<'
		&& str[0] != '>' && str[0] != '|')
		i = ft_strcpy(data, str, i, j);
	else if ((str[0] && str[1]) && ((str[0] == '>' && str[1] == '>')
			|| (str[0] == '<' && str[1] == '<')))
		i = ft_strcpy(data, str, 2, j);
	else if ((str[0]) && (str[0] == '<' || str[0] == '>' || str[0] == '|'))
		i = ft_strcpy(data, str, 1, j);
	if (ft_chopper(data, str + i, ++j, 0) == -1 || str[i] == '\0')
		data->token[j] = NULL;
	return (0);
}
*/

/*
	[Final]
int	ft_chopper(t_data *data, char *str, int j, int i)
{
	while (j < data->n_word)
	{
		i = 0;
		while (*str != '\0' && *str == ' ')
			str++;
		if (check_str_null(data, str, i, j) == -1)
			return (0);
		skip_normal_char(str, &i);
		if (str[i] != '\0' && str[i] == '\'')
			check_sq(data, &str, &i, &j);
		else if (str[i] != '\0' && (str[i] == '\"'))
			check_dq(data, &str, &i, &j);
		else if (str[0] != '\0' && str[0] != '<'
			&& str[0] != '>' && str[0] != '|')
			i = ft_strcpy(data, str, i, j);
		else if ((str[0] && str[1]) && ((str[0] == '>' && str[1] == '>')
				|| (str[0] == '<' && str[1] == '<')))
			i = ft_strcpy(data, str, 2, j);
		else if ((str[0]) && (str[0] == '<' || str[0] == '>' || str[0] == '|'))
			i = ft_strcpy(data, str, 1, j);
		str += i;
		j++;
	}
	data->token[j] = NULL;
	return (0);
}

int	ft_chopper(t_data *data, char *str, int j, int i)
{
	while (j < data->n_word)
	{
		i = 0;
		while (*str != '\0' && *str == ' ')
			str++;
		if (check_str_null(data, str, i, j) == -1)
			return (0);
		skip_normal_char(str, &i);
		if (str[i] != '\0' && str[i] == '\'')
			check_sq(data, &str, &i, &j);
		else if (str[i] != '\0' && (str[i] == '\"'))
			check_dq(data, &str, &i, &j);
		else if (str[0] != '\0' && str[0] != '<'
			&& str[0] != '>' && str[0] != '|')
			i = ft_strcpy(data, str, i, j);
		else if ((str[0] && str[1]) && ((str[0] == '>' && str[1] == '>')
				|| (str[0] == '<' && str[1] == '<')))
			i = ft_strcpy(data, str, 2, j);
		else if ((str[0]) && (str[0] == '<' || str[0] == '>' || str[0] == '|'))
			i = ft_strcpy(data, str, 1, j);
		str += i;
		j++;
	}
	data->token[j] = NULL;
	return (0);
}
*/

char	*dup_array(char **str, char *res)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		if (res == NULL)
			res = strdup(str[i]);
		else
		{
			tmp = strdup(res);
			free(res);
			res = ft_strjoin(tmp, str[i]);
			free(tmp);
		}
		i++;
	}
	return (res);
}

/*
	go through the string
	if ' skip
	set start to first '
	while not ' skip
	if current i is larger than start
	malloc and copy the string to tmp[j]
*/
char	**split_str_by_sq(char *str, int i, int j)
{
	int		start;
	char	**tmp;

	start = 0;
	tmp = (char **)malloc(sizeof(char *) * (100));
	if (tmp == NULL)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == '\'')
			i++;
		start = i;
		while (str[i] && str[i] != '\'')
			i++;
		if (i > start)
		{
			tmp[j] = (char *)malloc(sizeof(char) * ((i - start) + 1));
			if (tmp[j] == NULL)
				return (NULL);
			ft_cpy_str(tmp[j], &str[start], i - start);
			j++;
		}
	}
	tmp[j] = NULL;
	return (tmp);
}
