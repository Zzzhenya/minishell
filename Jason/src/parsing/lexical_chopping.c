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

/* [F]
    When "str" meet with single(double) quote(s).
	Cpy value of "str" to data->token struct.
	It works from meeting first ' to meeting end of last '.

	[Example]
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
	Index starts from '1'
	Copy '1' to int "k"			k = 1;
	From 1 to 5 // i++			i = 6;
	-------------------------------------------------------
	[Param]
			   p1       p2          p3       p4
	ft_strcpy(data, str + 1(k), 6(i) - 1(k), 0);
	
	p1: data struct
	p2: *(str + 1) // Now "str" starts from 2nd char('a')
	p3: len = 5
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
*/
char	*case_s_quote(t_data *data, char *str, int i, int j)
{
	int	k;

	k = i;
	while (str[i] != '\'' && str[i] != '\0')
		i++;
	ft_strcpy(data, str + k, i - k, j);
	return (str + i);
}

/* [F]
	Same as [f] case_s_quote.
*/
char	*case_d_quote(t_data *data, char *str, int i, int j)
{
	int	k;

	k = i;
	while (str[i] != '\"' && str[i] != '\0')
		i++;
	ft_strcpy(data, str + k, i - k, j);
	return (str + i);
}

/* [F]
    [Goal]
    If str isn't allocated memeory -> return (-1)
    If User_input is NULL, make data->token[0] NULL.
    

    [Param]
    (1): t_data
    (2): str // user_input
    (3): i = 0; (start)
    (4): j = 0; (start)
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

/* [F]
	[Form]
	ft_chopper(&data, user_input, 0)

	[Param]
    1. t_data *data
        typedef struct s_data
        {
            int		word_num;
            -> [func]"count_word"	-> how many words
            
            int		n_sq;
            -> [func]"count_quote"	-> how many single quote
            
            int		n_dq;
            -> [func]"count_quote"	-> how many double quotes
            
            char	**token;
            -> [malloc]			-> Token for each words (first dimension)
            
            char	*str;
            -> [param] "user_input"	-> original input from user
        }	t_data;
    2. char *str: user_input: "ls -l | cat -e 'a  b'bc"
    3. j: start from 0.

	[Description in oder of progree]
	1. 입력이 비어있는 경우를 처리
	2. 공백을 건너뛰고, 단어의 시작 위치를 찾음
	3. 문자열의 끝에 도달하면 함수 종료
	4. 단어의 끝까지 진행하여 토큰을 찾음
	5. 각 경우에 따라 토큰을 처리하여 저장
	6. 재귀 호출을 통해 다음 토큰 처리
	7. 재귀 호출이 끝난 경우 -> 배열의 마지막에 NULL 포인터 설정.
*/
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
