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

/*	[F]
	If "c" is !!!not!!! in "str"	->	return (-1)
	Else							->	return (i)
*/
int	ft_strchr_m(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

/*	[F]
	If compare s1 != s2	-> return (s1-s2)
	Else				-> return (0)
*/
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (*s1 - *s2);
	return (0);
}

/*	[F]
*/
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*	[F]
	If "c" is not in "str"	->	return (-1)
	Else					->	return (i)
*/
int	ft_putstr_m(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}

/*	[F]
	[Form & Param]
	find_matching_env_row(data->token[i] + column_index_dollar + 1, env);

	i번째 토큰에서 발견한($)기호 다음(+1)문자부터 검색을 시작한다.

	[Role]
	If str is founded after $ from env,

	[Return]
	'i': 환경변수에서 발견한 스트링이 시작되는 인덱스를 반환한다.
*/
int	find_matching_env_row(char *str, char **env)
{
	int	i;

	i = 0;
	if (str == NULL && *str == '\0')
		return (-1);
	while (env[i] != NULL)
	{
		if (ft_strcmp(env[i], str) != -1)
			return (i); 
		i++;
	}
	return (-1);
}

/*	[F]
	[Example]
	1. str: 'abc d'
		 [0] [1] [2] [3] [4] [5] [6] [7]
	str:  '   a   b   c       d   '  \0

	2. delete str[6]: ' and cpy \0 to here.
		 [0] [1] [2] [3] [4] [5] [6]
	str:  '   a   b   c       d  \0

	3. Allocate 6 memories(len(7) - 1) for "res".
		 [0] [1] [2] [3] [4] [5]
	res: 

	4. copy str, starting with [i + 1] to res[i]
		 [0] [1] [2] [3] [4] [5]
	res:  a   b   c       d  \0

	5. Result
	res: [a][b][c][ ][d]
	
	Success to trim quotes which was located in both sides of string.
*/
char	*trim_single_quotes(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = ft_strlen(str);
	res = (char *)malloc((len - 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	str[len - 1] = '\0';	// replace ' with \0
	while (str[i] != '\0')
	{
		res[i] = str[i + 1];
		i++;
	}
	free(str);
	return (res);
}
// [Q & A]
//	Why free(str) here?
//	= In the trim_single_quotes function,
//	  after copying the ri_replace_struired characters into the res string,
//	  str is no longer needed because its contents have been duplicated into "res".

/*	[F]
	[Param]
		param(1): data	// Data struct from [f]validate
		param(2): i		// Which order of token does is coreespond to?
						// token[0]? token[1]? token[2]? token[3]?
*/
int	remove_single_quotes_from_token(t_data *data, int i)
{
	data->token[i] = trim_single_quotes(data->token[i]);
	if (data->token[i] == NULL)
		return (-1);
	return (0);
}

/*	[F]
	[Form]
	data->token[i] = replace_substring(data->token[i], env[row_matched_env], column_index_dollar);

	[Role]
	copy new token to old token. (= replace)

	[Where is "HOME" in env?]
		env | grep -n USER" // 12 line(= row)

	[Param]												   
	token[0] = $HOME		*env[row_matched_env = 12] == HOME=/home/tkwak
	token[0][0] = $
	token[0][1] = H		 	column_index_dollar: 0
	token[0][2] = O			= Dollar positied in first letter here.
	token[0][3] = M
	token[0][4] = E			When token is "abc$HOME" -> 'abc' just cpy to new string.

	[Variable]
	i_replace_str: index after '=' in row_matched_env. (= 5)

	row_matched_env		==	Pointer to 'H'	==	"HOME=/home/tkwak"
	row_matched_env + 5	==	Pointer to '/'	==	"/home/tkwak"
	ft_strlen (row_matched_env + 5)			==	11 (= length of str from '/' to the end)

	malloc(11 + column_index_dollar + 1) == malloc(11 + 0 + 1) == malloc(12)

	Copy contents from "env" corresponding to after '=' sign to "res".
*/
char	*replace_substring(char *token, char *row_matched_env, int column_index_dollar)
{
	int		i;
	int		i_replace_str;
	char	*res;

	i = 0;
	i_replace_str = ft_strchr_m(row_matched_env, '=') + 1;	// Jump to after '=' sign.
	res = (char *)malloc((ft_strlen(row_matched_env + i_replace_str) + column_index_dollar + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < column_index_dollar)		// Before meet with $ sign, just cpy to "res".
	{
		res[i] = token[i];
		i++;
	}
	while (row_matched_env[i_replace_str] != '\0')
	{
		res[i] = row_matched_env[i_replace_str];	// cpy "/home/tkwak" to res[i]
		i++;
		i_replace_str++;
	}
	res[i] = '\0';
	free(token);
	return (res);
}
/*	
	[Example]
	if no row_matched_env, result of [f]find_matching_env_row == -1.
		replace_substring(data->token[i], "\n", column_index_dollar);

	*token[i] = "$abcd"

	i_replace_str = ft_strchr_m('\n', '=') -> return (-1) + 1
				  = -1 + 1 = 0
	
	malloc(ft_strlen(1) + 0 + 1) == malloc(2)
								 	res[0] = \n
								 	res[1] = '\0'
*/

/*	[F]
	[Goal]
	ft_chopper function splits user_input into specific tokens.
	"Expand_env" expands the token with $,
	which represents an environment variable,
	to the value of the actual environment variable.
	= 주어진 문자열에서 환경 변수를 발견하고, 해당 환경 변수를 실제 값으로 대체합니다.
	= User_input 분할 된 토큰 중 $이 붙은 환경변수 관련 토큰을 찾아
	  실제 환경변수 값으로 취급 될 수 있도록 만들어주는 함수.

	[Example]
	user_input: "echo $HOME | cat -e"
					  -----
					  "env": $ is attached in front of word.
					   It should be treated not as "word" (H O M E)
					    					but as "env" (/home/tkwak)

	[Form & Param]
	expand_env(&data, env, 0)
		param1: data struct from [f]validate.
		param2: env from [f]main.c
		param3: index for the tokens's order
				token[0]: echo
				token[1]: $HOME
				token[2]: |
				token[3]: cat
				token[4]: -e

	[Exceptional case]
	(1) echo '$HOME'	// Must be string, even if $(dollar sign) is inside between sigle quotes.
	(2) echo $?			// EXIT STATUS
	(3) echo $$			// CURR SHELL'S	PID

	[Process]
	Search "$", if there is
	-> Check exceptional cases
	-> Find
*/
int	expand_env(t_data *data, char **env, int i)
{
	int	column_index_dollar;
	int	row_matched_env;

	while (data->token[i] != NULL) // Check all tokens(token[0], token[1], token[2], ...)
	{
		column_index_dollar = ft_strchr_m(data->token[i], '$');			// Check '$' sign in token.
		if (column_index_dollar != -1
			&& (ft_strchr_m(data->token[i], '\'') == -1)				// Exceptional case(1): != echo '$' // There isn't (')
			&& data->token[i][column_index_dollar + 1] != '?'			// Exceptional case(2): != echo $?	// Next char isn't (?)
			&& data->token[i][column_index_dollar + 1] != '$')			// Exceptional case(3): != echo $$ // $: (token[i]) $ (token[i] + 1)
		{
			row_matched_env = find_matching_env_row(data->token[i] + column_index_dollar + 1, env); // Pointer to after $ (dollar sign).
			if (row_matched_env == -1)	// If there is $ sign but not related with ENV
			{
				data->token[i] = replace_substring(data->token[i], "\n", column_index_dollar);		// cpy "\n\0" to token[i].
				return (0);
			}
			data->token[i] = replace_substring(data->token[i], env[row_matched_env], column_index_dollar);
			if (data->token[i] == NULL)
				return (-1);
		}
		else if (data->token[i][0] == '\'') // Case: 'str' starts from single_quote(')
		{
			if (remove_single_quotes_from_token(data, i) == -1);
				return (-1);
		}
		i++;
	}
	return (0);
}
/*
	[ Example ]
	(Case1)
		token[0] = echo
		token[1] = $HOME
		= echo /home/tkwak

	(Case2)
		token[0] = echo
		token[1] = $abcd
		= echo \n
		= 실제로 배쉬에서 $표시가 있는데 환경변수에 없는 내용일 경우 \n을 출력한다.
*/

/*
[ Original form without comment ]
int	expand_env(t_data *data, char **env, int i)
{
	int	column_index_dollar;
	int	row_matched_env;

	while (data->token[i] != NULL) // Check all tokens(token[0], token[1], token[2], ...)
	{
		column_index_dollar = ft_strchr_m(data->token[i], '$');
		if (column_index_dollar != -1
			&& (ft_strchr_m(data->token[i], '\'') == -1)
			&& data->token[i][column_index_dollar + 1] != '?'
			&& data->token[i][column_index_dollar + 1] != '$')
		{
			row_matched_env = find_matching_env_row(data->token[i] + column_index_dollar + 1, env);
			if (row_matched_env == -1)
			{
				data->token[i] = replace_substring(data->token[i], "\n", column_index_dollar);
				return (0);
			}
			data->token[i] = replace_substring(data->token[i], env[row_matched_env], column_index_dollar);
			if (data->token[i] == NULL)
				return (-1);
		}
		else if (data->token[i][0] == '\'') // Case: 'str' starts from single_quote(')
		{
			if (remove_single_quotes_from_token(data, i) == -1);
				return (-1);
		}
		i++;
	}
	return (0);
}
*/
