#include <stdlib.h>
#include <stdio.h>

typedef struct s_data
{
	int		n_word;
	int		n_sq;
	int		n_dq;
	char	**token;
	char	*str;
}	t_data;

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
    cpy (str) to data.token
*/
// int	ft_strcpy(t_data *data, char *str, int len, int j)
// {
// 	int	i;
// 	int	index;

// 	i = 0;
// 	while (ft_isspace(str[i]))
// 		i++;
// 	data->token[j] = malloc((len + 1) * sizeof(char));
// 	if (!data->token[j])
// 		return (-1);
// 	index = 0;
// 	while (i < len)
// 	{
// 		data->token[j][index] = str[i];
// 		i++;
// 		index++;
// 	}
// 	data->token[j][index] = '\0';
// 	return (len);
// }

/* [F]
    Same with ft_strcpy.
	But only use for normal character (!= |, >, <, ', "..)
*/
int	ft_strcpy2(t_data *data, char *str, int len, int j)
{
	int	i;
	int	index;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	data->token[j] = malloc((len + 1) * sizeof(char));
	if (!data->token[j])
		return (-1);
	index = 0;
	while (i < len && str[i] != ' ')
	{
		data->token[j][index] = str[i];
		i++;
		index++;
	}
	data->token[j][index] = '\0';
	return (len);
}

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
	skip normal character on the string.
*/
// void	skip_normal_char(char *str, int *i)
// {
// 	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '='
// 		&& str[*i] != '\"' && str[*i] != '\''
// 		&& str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
// 		*i += 1;
// }

/* [F]
	skip ' 'space in str
*/
void	skip_space_in_str(char *str, int *i)
{
	while (ft_isspace(str[*i]) == -1)
		*i += 1;
	return ;
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
            int		word_num;	-> [func]"count_word"	-> how many words
            int		n_sq;		-> [func]"count_quote"	-> how many single quote
            int		n_dq;		-> [func]"count_quote"	-> how many double quotes
            char	**token;	-> [malloc]				-> Token for each words (first dimension)
            char	*str;		-> [param] "user_input"	-> original input from user
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
// 	skip_normal_char(str, &i);
// 	skip_space_in_str(str, &i);
// 	printf("\t 2. current str: %s\n", str);
// 	if (str[0] == '\'')
// 		str = case_s_quote(data, str, i + 1, j);
// 	else if (str[0] == '\"')
// 		str = case_d_quote(data, str, i + 1, j);
// 	else if (str[0] != '=' && str[0] != '\0'
// 		&& str[0] != '<' && str[0] != '>' && str[0] != '|')
// 		ft_strcpy2(data, str, i, j);
// 	else if ((str[0] == '>' && str[1] == '>')
// 		|| (str[0] == '<' && str[1] == '<'))
// 		i = ft_strcpy(data, str, 2, j);
// 	else if (str[0] == '=' || str[0] == '<' || str[0] == '>' || str[0] == '|')
// 			i = ft_strcpy(data, str, 1, j);
// 	if (ft_chopper(data, str + i, ++j) == -1 || str[i] == '\0')
// 		data->token[j] = NULL;
// 	return (0);
// }
/*
	[Q1]
	Use "user_input" as a parameter directly instead of data.str(= already cpy user_input to str)
	= In [F] count_word, str's starting pointer is already modified.
*/

void	toggle_inword_inquote(int *flag_inword, int *n_word, int *flag_inquote)
{
	if (*flag_inquote == 1)
	{
		*n_word += 1;
		*flag_inword = 0;
		*flag_inquote = 0;
	}
	else
	{
		*flag_inword = 1;
		*flag_inquote = 1;
	}
	return ;
}

int	count_word(const char *str, int n_word, int flag_inword, int flag_inquote)
{
	while (*str)
	{
		if (*str == ' ' && flag_inquote == 0)
			flag_inword = 0;
		else if (*str == '=' || *str == '<' || *str == '>'
			|| *str == '|' || *str == '$')
		{
			n_word++;
			flag_inword = 0;
		}
		else if (*str == '"' || *str == '\'')
			toggle_inword_inquote(&flag_inword, &n_word, &flag_inquote);
		else
		{
			if (flag_inword == 0)
			{
				n_word++;
				flag_inword = 1;
			}
		}
		str++;
	}
	return (n_word);
}

/*
// Must fix !!!
char	**validate_input(char *user_input, char **env)
{
	t_data	data;

	data.tmp = user_input;
	if (count_quote(user_input, &data) == -1)
		return (NULL);
	data.word_num = count_word(data.tmp, 0, 0, 0);
	if (data.word_num == 0)
		return (NULL);
	if (data.n_sq + data.n_dq > 0)
		if (check_order_quote(user_input, &data, 0, 0) == -1)
			return (NULL);
	data.token = malloc((data.word_num + 1) * sizeof(char *));
    if (data.token == NULL)
        return (NULL);
	if (ft_chopper(&data, user_input, 0) == -1)
		return (NULL);
	if (expansion(&data, env, 0) == -1)
		return (NULL);
	return (data.token);
}
*/

// int	main(void)
// {
// 	char	*input;
// 	int		result;
// 	t_data	data;

// 	input = "  ls -l $$ | cat -e 'a  b'bc";
// 	data.n_word = count_word(input, 0, 0, 0);
// 	data.n_sq = 0;
// 	data.n_dq = 0;
// 	data.str = input;
// 	data.token = malloc(((data.n_word) + 1) * sizeof(char *));
// 	printf("\n\t 1. n_word: %d\n\n", data.n_word);
// 	if (!data.token)
// 	{
// 		printf("Fail to allocate memory\n");
// 		return (1);
// 	}
// 	result = ft_chopper(&data, input, 0);
// 	if (result != -1)
// 	{
// 		printf("\n\t 3. input: %s\n\n", input);
// 		for (int i = 0; data.token[i] != NULL; i++)
// 			printf("\t 4. data.token[%d]:%s\n", i, data.token[i]);
// 	}
// 	else
// 		printf("Error.\n");
// 	for (int i = 0; data.token[i] != NULL; i++)
// 		free(data.token[i]);
// 	free(data.token);
// 	return (0);
// }
