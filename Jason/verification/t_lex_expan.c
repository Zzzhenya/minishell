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
	If "c" is not in "str"	->	return (-1)
	Else					->	return (i)
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

/* [F]
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

/* [F]
*/
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* [F]
	If "c" is not in "str"	->	return (-1)
	Else					->	return (i)
*/
int	ft_putstr_m(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}

/* [F]
	[Form & Param]
	find_matching_env(data->token[i] + index_dollar + 1, env);

	i번째 토큰에서 발견한($)기호 다음(+1)문자부터 검색을 시작한다.

	[Role]
	If str is founded after $ from env,
	return (i) // 'i': 환경변수에서 발견한 스트링이 시작되는 인덱스
*/
int	find_matching_env(char *str, char **env)
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

/* [ ]
*/
char	*str_modifier(char *str, char *var, int d)
{
	int		eq;
	int		i;
	char	*res;

	i = 0;
	eq = ft_strchr_m(var, '=') + 1;
	res = (char *)malloc((ft_strlen(var + eq) + d + 1) * sizeof(char));
	while (i < d)
	{
		res[i] = str[i];
		i++;
	}
	while (var[eq] != '\0')
	{
		res[i] = var[eq];
		i++;
		eq++;
	}
	res[i] = '\0';
	free(str);
	return (res);
}

/* [F]

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

	4. copy str[i + 1] to res[i]

		 [0] [1] [2] [3] [4] [5]
	res:  a   b   c       d  \0

	5. res: [a][b][c][ ][d]
	
	Success to trim quotes which was located in both sides of string.
*/
// char	*trim_single_quotes(char *str)
// {
// 	int		i;
// 	int		len;
// 	char	*res;

// 	i = 0;
// 	len = ft_strlen(str);
// 	res = (char *)malloc((len - 1) * sizeof(char));
// 	if (res == NULL)
// 		return (NULL);
// 	str[len - 1] = '\0';	// replace ' with \0
// 	while (str[i] != '\0')
// 	{
// 		res[i] = str[i + 1];
// 		i++;
// 	}
// 	free(str);
// 	return (res);
// }
// [Q][A]
//	Why free(str) here?
//	= In the trim_single_quotes function,
//	  after copying the required characters into the res string,
//	  str is no longer needed because its contents have been duplicated into "res".

/* [F]
	[Param]
		param(1): data	// Data struct from [f]validate
		param(2): i		// Which order of token does is coreespond to?
						// token[0]? token[1]? token[2]? token[3]?
*/
// int	remove_single_quotes_from_token(t_data *data, int i)
// {
// 	data->token[i] = trim_single_quotes(data->token[i]);
// 	if (data->token[i] == NULL)
// 		return (-1);
// 	return (0);
// }

/* [ ]
	[Goal]
	ft_chopper function splits user_input into specific tokens.
	"Expand_env" expands the token with $,
	which represents an environment variable,
	to the value of the actual environment variable.
	= user_input 분할 된 토큰 중 $이 붙은 환경변수 관련 토큰을 찾아
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
		param3: index

	[Exceptional case]
	(1) echo '$HOME'	// Must be string, even if $(dollar sign) is inside between sigle quotes.
	(2) echo $?			// EXIT STATUS
	(3) echo $$			// CURR SHELL'S	PID
*/
// int	expand_env(t_data *data, char **env, int i)
// {
// 	int	index_dollar;
// 	int	index_matching_env;

// 	while (data->token[i] != NULL) // Check all tokens(token[0], token[1], token[2], ...)
// 	{
// 		index_dollar = ft_strchr_m(data->token[i], '$');	// Check $ sign in token. No '$' -> d: -1
// 		if (index_dollar != -1
// 			&& (ft_strchr_m(data->token[i], '\'') == -1)		// Exceptional case(1): echo '$'
// 			&& data->token[i][index_dollar + 1] != '?'		// Exceptional case(2): echo $?
// 			&& ft_strchr_m(data->token[i] + 1, '$') == NULL)	// Exceptional case(3): echo $$
// 		{
// 			index_matching_env = find_matching_env(data->token[i] + index_dollar + 1, env);

// --------------------------------over here------ finish---------------------------------------

// 			if (index_matching_env == -1)
// 			{
// 				data->token[i] = str_modifier(data->token[i], "\n", index_dollar);
// 				return (0);
// 			}
// 			data->token[i] = str_modifier(data->token[i], env[index_matching_env], index_dollar);
// 			if (data->token[i] == NULL)
// 				return (-1);
// 		}

// --------------------------------under here------ finish---------------------------------------

// 		else if (data->token[i][0] == '\'') // Case: str starts from single_quote(')
// 		{
// 			if (remove_single_quotes_from_token(data, i) == -1);
// 				return (-1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

/*
int	expand_env(t_data *data, char **env, int i)
{
	int	index_dollar;
	int	v;

	while (data->token[i] != NULL)
	{
		index_dollar = ft_strchr_m(data->token[i], '$');
		if (index_dollar != -1
			&& (ft_strchr_m(data->token[i], '\'') == -1)
			&& data->token[i][index_dollar + 1] != '?'
			&& ft_strchr_m(data->token[i] + 1, '$') == NULL)
		{
			v = find_matching_env(data->token[i] + index_dollar + 1, env);
			if (v == -1)
			{
				data->token[i] = str_modifier(data->token[i], "\n", index_dollar);
				return (0);
			}
			data->token[i] = str_modifier(data->token[i], env[v], index_dollar);
			if (data->token[i] == NULL)
				return (-1);
		}
		else if (data->token[i][0] == '\'') // Case: str starts from single_quote(')
		{
			if (remove_single_quotes_from_token(data, i) == -1);
				return (-1);
		}
		i++;
	}
	return (0);
}
*/