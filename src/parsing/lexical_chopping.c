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

void	check_sq(t_data *data, char **str, int *i, int *j)
{
	if (*i != 0)
		*i = 0;
	case_s_quote(data, *str, *i, *j);
}

void	check_dq(t_data *data, char **str, int *i, int *j)
{
	if (*i != 0)
		*i = 0;
	case_d_quote(data, *str, *i, *j);
}
/*
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
*/

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

/*
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

/*
// [ 6TH ] Ramesh
int	ft_chopper(t_data *data, char *str, int j)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (-1);
	while (str[i] == ' ')
		str++;
	if (check_str_null(data, str, i, j) == -1)
		return (0);
	skip_normal_char(str, &i);
	if (str[i] == '\'')
	{
		if (i != 0)
			i = 0;
		str = case_s_quote(data, str, i, j);
	}
	else if (str[i] == '\"')
	{
		if (i != 0)
			i = 0;
		str = case_d_quote(data, str, i, j);
	}
	else if (str[0] != '\0' && str[0] != '<' && str[0] != '>' && str[0] != '|')
		i = ft_strcpy(data, str, i, j);
	else if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<'))
		i = ft_strcpy(data, str, 2, j);
	else if (str[0] == '<' || str[0] == '>' || str[0] == '|')
		i = ft_strcpy(data, str, 1, j);
	if (str[i] == '\0')
		return (0);
	printf("this is str + i **%s**\n", str+i);
	if (ft_chopper(data, str + i, ++j) == -1) // str[i] == '\0'
	{
		// free(data->token[j]);
		data->token[j] = NULL;
	}
	return (0);
}
*/

// [ 5TH ]
// int	ft_chopper(t_data *data, char *str, int j)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] == '\0')
// 		return (-1);
// 	while (str[i] == ' ')
// 		str++;
// 	str += i;
// 	i = 0;
// 	if (check_str_null(data, str, i, j) == -1)
// 		return (0);
// 	skip_normal_char(str, &i);
// 	if (str[i] == '\'')
// 		check_sq(data, &str, &i, &j);
// 	else if (str[i] == '\"')
// 		check_dq(data, &str, &i, &j);
// 	else if (str[0] != '\0' && str[0] != '<' && str[0] != '>' && str[0] != '|')
// 		i = ft_strcpy(data, str, i, j);
// 	else if ((str[0] == '>' && str[1] == '>')
//			|| (str[0] == '<' && str[1] == '<'))
// 		i = ft_strcpy(data, str, 2, j);
// 	else if (str[0] == '<' || str[0] == '>' || str[0] == '|')
// 		i = ft_strcpy(data, str, 1, j);
// 	printf("curr 'j': %d\n", j);
// 	// int n = ft_strlen(str);
// 	// if (i < 0 || i >= n)
// 	// 	return (-1);
// 	if (ft_chopper(data, str + i, ++j) == -1 || str[i] == '\0')
// 		data->token[j] = NULL;
// 	return (0);
// }

/*
// [ 4TH ]
int	ft_chopper(t_data *data, char *str, int j)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (-1);
	while (str[i] == ' ')
		str++;
	if (check_str_null(data, str, i, j) == -1)
		return (0);
	skip_normal_char(str, &i);
	printf("1. curr 'i': %d\n", i);
	if (str[i] == '\'')
	{
		if (i != 0)
			i = 0;
		str = case_s_quote(data, str, i, j);
		printf("1. str: %s\n", str);
	}
	else if (str[i] == '\"')
	{
		if (i != 0)
			i = 0;
		str = case_d_quote(data, str, i, j);
	}
	else if (str[0] != '\0' && str[0] != '<' && str[0] != '>' && str[0] != '|')
		i = ft_strcpy(data, str, i, j);
	else if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<'))
		i = ft_strcpy(data, str, 2, j);
	else if (str[0] == '<' || str[0] == '>' || str[0] == '|')
		i = ft_strcpy(data, str, 1, j);
	if (ft_chopper(data, str + i, ++j) == -1 || str[i] == '\0')
		data->token[j] = NULL;
	return (0);
}
*/

/*
[ 3RD ]
char	*ft_norm(t_data *data, char *str, int i, int j)
{
	char	*res;

	if (i != 0)
		i = 0;
	if (str[i] == '\'')
		res = case_s_quote(data, str, i, j);
	else
		res = case_d_quote(data, str, i, j);
	return (res);
}

char	*handle_quote(t_data *data, char *str, int *i, int j)
{
	if (str[*i] == '\'')
	{
		if (*i != 0)
			*i = 0;
		str = case_s_quote(data, str, *i, j);	// malloc
		if (str == NULL)
			return (NULL);
	}
	else if (str[*i] == '\"')
	{
		if (*i != 0)
			*i = 0;
		str = case_d_quote(data, str, *i, j);	// malloc
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

int	ft_chopper_part1(t_data **data, char **str, int *i, int *j)
{
	if (*str[0] == '\0')
		return (-1);
	while (*str[*i] == ' ')
		(*str)++;
	if (check_str_null(*data, *str, *i, *j) == -1)
		return (-1);
	skip_normal_char(*str, &*i);
	return (0);
}

int	ft_chopper(t_data *data, char *str, int j)
{
	int	i;

	i = 0;
	if (ft_chopper_part1(&data, &str, &i, &j) == -1)
		return (-1);
	if (str[i] == '\'')
	{
		if (i != 0)
			i = 0;
		str = case_s_quote(data, str, i, j);	// malloc
		printf("1. str: %s\n", str);
	}
	else if (str[i] == '\"')
	{
		if (i != 0)
			i = 0;
		str = case_d_quote(data, str, i, j);	// malloc
	}
	if (str[i] != '\0' && str[i] != '<' && str[i] != '>' && str[i] != '|')
		i = ft_strcpy(data, str, i, j);
	else if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<'))
		i = ft_strcpy(data, str, 2, j);
	else if (str[0] == '<' || str[0] == '>' || str[0] == '|')
		i = ft_strcpy(data, str, 1, j);
	if (ft_chopper(data, str + i, ++j) == -1 || str[i] == '\0')
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
