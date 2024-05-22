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

/*	[F]
    [ Goal ]
    If str isn't allocated memeory -> return (-1)
    If User_input is NULL, make data->token[0] NULL.
    
    [ Param ]
    (1): t_data
    (2): str // user_input
    (3): i = 0; (start)
    (4): j = 0; (start)

	if (str == NULL)
		return (-1);
*/
int	check_str_null(t_data *data, char *str, int i, int j)
{
	if (str[i] == '\0')
	{
		data->token[j] = NULL;
		return (-1);
	}
	return (0);
}

char	*meet_space_1(t_data *data, char **str, int *i, int *j)
{
	ft_strcpy(data, *str, (*i) + 1, *j);
	(*i)++;
	*str = (*str) + (*i) + 1;
	return (*str);
}

char	*meet_space_2(t_data *data, char **str, int *i, int *j)
{
	ft_strcpy(data, *str, *i, *j);
	(*i)++;
	*str = *str + *i;
	return (*str);
}

/*	[F]
	[ Process ]
    When "str" meet with single(double) quote(s).
	Cpy value of "str" to data->token struct.
	It works from the meeting with first '(sq)
			   to the meeting with end   '(sq)

	[ Example ]
	*str	'ab   c'
	---------------------
	  index	  value
	str[0]:		'
	str[1]:		a
	str[2]:		b
	str[3]:	   
	str[4]:	   
	str[5]:		c
	str[6]:		'
	---------------------
	Index starts from '0'
	Copy '1' to int "k"			k = 1;
	From 1 to 5 // i++			i = 6;
	-------------------------------------------------------
	[Param]
			   p1       p2          p3       p4
	ft_strcpy(data, str + 1(k), 6(i) - 1(k), 0);
	ft_strcpy(data, str + 1 , 5, 0);
	
	p1: data struct
	p2: *(str + 1)	// Now "str" starts from 2nd char('a')
	p3: len = 5		// From 2nd char, cpy 5 charactors.
	p4: j = 0
	-------------------------------------------------------
	[Local variable]
	i = 0;
	index = 0;
	-------------------------------------------------------
	malloc (len + 1) == 6boxes.
	[ ] [ ] [ ] [ ] [ ] [ ]
	------------------------------------------------
	Cpy str to data.token

	while (i < len)	// 0 < 5
		data.token[j][index] = str[i]
		i++, index++

			   		   j index     i  value
	box1:	data.token[0][0] = str[0]: a
	box2:	data.token[0][1] = str[1]: b
	box3:	data.token[0][2] = str[2]: ' '
	box4:	data.token[0][3] = str[3]: ' '
	box5:	data.token[0][4] = str[4]: c
	------------------------------------------------
	box6:	data.token[0][5] =		   \0
	------------------------------------------------


	[ TEST ]
	P/F		string						n_word
	[ ]		' ' abc'a b'aa 'abc'			3
	[ ] 	''aaa'    aa'aa''				1
	[ ]		'abc' ababab'b'b				2
	[ ]		abc's'a 'a'						2
	[ ]		abc'ab' ddd'd'd					2
	[ ]		'abc'aa aba ''a'a'				3
	[ ] 	a a'a' a' a' a'a ' a' a '		5
	[ ]		'' aa ''						3
*/
char	*case_s_quote(t_data *data, char *str, int i, int j)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			data->n_sq--;
			if (data->n_sq % 2 == 0)
			{
				if (str[i + 1] != '\0' && str[i + 1] == ' ')
					return (meet_space_1(data, &str, &i, &j));
			}
		}
		else
		{
			if (str[i + 1] != '\0' && str[i + 1] == ' ' && data->n_sq % 2 == 0)
				return (meet_space_1(data, &str, &i, &j));
		}
		i++;
	}
	return (meet_space_2(data, &str, &i, &j));
}

// char	*case_s_quote(t_data *data, char *str, int i, int j)
// {
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'')
// 		{
// 			data->n_sq--;
// 			if (data->n_sq % 2 == 0)
// 			{
// 				if (str[i + 1] != '\0' && str[i + 1] == ' ')
// 				{
// 					ft_strcpy(data, str, (i) + 1, j);
// 					(i)++;
// 					str = (str) + (i) + 1;
// 					return (str);
// 				}
// 					// return (meet_space_1(data, &str, &i, &j));
// 			}
// 		}
// 		else
// 		{
// 			if (str[i + 1] != '\0' && str[i + 1] == ' ' && data->n_sq % 2 == 0)
// 			{
// 				ft_strcpy(data, str, (i) + 1, j);
// 				(i)++;
// 				str = (str) + (i) + 1;
// 				return (str);
// 			}
// 				// return (meet_space_1(data, &str, &i, &j));
// 		}
// 		i++;
// 	}
// 	return (meet_space_2(data, &str, &i, &j));
// }

char	*case_d_quote(t_data *data, char *str, int i, int j)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			data->n_dq--;
			if (data->n_dq % 2 == 0)
			{
				if (str[i + 1] != '\0' && str[i + 1] == ' ')
					return (meet_space_1(data, &str, &i, &j));
			}
		}
		else
		{
			if (str[i + 1] != '\0' && str[i + 1] == ' ' && data->n_dq % 2 == 0)
				return (meet_space_1(data, &str, &i, &j));
		}
		i++;
	}
	return (meet_space_2(data, &str, &i, &j));
}

/*
    [ Original ]

char	*case_s_quote(t_data *data, char *str, int i, int j)
{
	int	k;

	k = i;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			data->n_sq--;
			if (data->n_sq % 2 == 0)
			{
				if (str[i + 1] != '\0' && str[i + 1] == ' ')
				{
					ft_strcpy(data, str, i + 1, j); // str + k
					i++;
					str = str + i + 1;
					return (str);
				}
			}
		}
		else
		{
			if (str[i + 1] == ' ' && data->n_sq % 2 == 0 && str[i + 1] != '\0')
			{
				ft_strcpy(data, str, i + 1, j);
				i++;
				str = str + i + 1;
				return (str);
			}
		}
		i++;
	}
	ft_strcpy(data, str, i, j);
	i++;
	str = str + i;
	return (str);
}

char	*case_d_quote(t_data *data, char *str, int i, int j)
{
	int	k;

	k = i;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			data->n_dq--;
			if (data->n_dq % 2 == 0)
			{
				if (str[i + 1] != '\0' && str[i + 1] == ' ')
				{
					ft_strcpy(data, str + k, i + 1, j);
					i++;
					str = str + i + 1;
					return (str);
				}
			}
		}
		else
		{
			if (str[i + 1] == ' ' && data->n_dq % 2 == 0 && str[i + 1] != '\0')
			{
				ft_strcpy(data, str, i + 1, j);
				i++;
				str = str + i + 1;
				return (str);
			}
		}
		i++;
	}
	ft_strcpy(data, str, i, j);
	i++;
	str = str + i;
	return (str);
}
*/