/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:12:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/27 20:15:35 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	[F]
	[Form & Param]
	find_matching_env_row(data->token[i] + i_dollar + 1, env);

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
	str[len - 1] = '\0';
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
//	  after copying the ri_newuired characters into the res string,
//	  str is no longer needed because
//	  its contents have been duplicated into "res".

/*	[F]
	[Param]
		param(1): data	// Data struct from [f]validate
		param(2): i	// Which order of token does is coreespond to?
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
	data->token[i] = replace_substring(data->token[i],
				env[row_env], i_dollar);

	[Role]
	copy new token to old token. (= replace)

	[Where is "HOME" in env?]
		env | grep -n USER" // 12 line(= row)

	[Param]												   
	token[0] = $HOME		*env[row_env = 12] == HOME=/home/tkwak
	token[0][0] = $
	token[0][1] = H		 	i_dollar: 0
	token[0][2] = O			= Dollar positied in first letter here.
	token[0][3] = M
	token[0][4] = E			When token is "abc$HOME" -> 'abc' just cpy to new string.

	[Variable]
	i_new: index after '=' in row_env. (= 5)

	row_env		==	Pointer to 'H'	==	"HOME=/home/tkwak"
	row_env + 5	==	Pointer to '/'	==	"/home/tkwak"
	ft_strlen (row_env + 5)			==	11 (= length of str from '/' to the end)

	malloc(11 + i_dollar + 1) == malloc(11 + 0 + 1) == malloc(12)

	Copy contents from "env" corresponding to after '=' sign to "res".

	[Process]
	1. ft_strchr_m: Jump to after '=' sign.
	2. (i < i_dollar): Before meet with $ sign, just cpy to "res".
	3. res[i] = row_env[i_new]: cpy "/home/tkwak" to res[i]
*/
char	*replace_substring(char *token, char *row_env, int i_dollar)
{
	int		i;
	int		i_new;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(row_env, '=') + 1;
	res = malloc((ft_strlen(row_env + i_new) + i_dollar + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < i_dollar)
	{
		res[i] = token[i];
		i++;
	}
	while (row_env[i_new] != '\0')
	{
		res[i] = row_env[i_new];
		i++;
		i_new++;
	}
	res[i] = '\0';
	free(token);
	return (res);
}
/*	
	[Example]
	if no row_env, result of [f]find_matching_env_row == -1.
		replace_substring(data->token[i], "\n", i_dollar);

	*token[i] = "$abcd"

	i_new = ft_strchr_m('\n', '=') -> return (-1) + 1
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
	(1) echo '$HOME'
		Must be string, even if $(dollar sign) is inside between sigle quotes.
	(2) echo $?
		EXIT STATUS
	(3) echo $$
		CURR SHELL'S	PID

	[Process]
	1. Check all tokens(token[0], token[1], token[2], ...)
	2. Check '$' sign in token.
	3. Check exceptional cases
		Exceptional case(1): != echo '$' // There isn't (')
		Exceptional case(2): != echo $?	// Next char isn't (?)
		Exceptional case(3): != echo $$ // $: (token[i]) $ (token[i] + 1)
	4. Pointer to after $ (dollar sign).
	5. If there is $ sign but not related with ENV
	6. Cpy "\n\0" to token[i].
	7. Check final case: 'str' starts from single_quote(')
*/
int	expand_env(t_data *data, char **env, int i)
{
	int	j;
	int	i_dollar;
	int	row_env;

	while (data->token[i] != NULL)
	{
		i_dollar = ft_strchr_m(data->token[i], '$');
		if (i_dollar != -1
			&& (ft_strchr_m(data->token[i], '\'') == -1) 
			&& data->token[i][i_dollar + 1] != '?' 
			&& data->token[i][i_dollar + 1] != '$')
		{
			row_env = find_matching_env_row(data->token[i] + i_dollar + 1, env);
			if (row_env == -1)
			{
				data->token[i] = replace_substring(data->token[i], "\n", i_dollar);
				return (0);
			}
			data->token[i]
				= replace_substring(data->token[i], env[row_env], i_dollar);
			if (data->token[i] == NULL)
				return (-1);
		}
		else if (data->token[i][0] == '\'')
		{
			if (remove_single_quotes_from_token(data, i) == -1)
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
		token[1] = aaa$HOME
		= echo /home/tkwak

	(Case2)
		token[0] = echo
		token[1] = $abcd
		= echo \n
		= 실제로 배쉬에서 $표시가 있는데 환경변수에 없는 내용일 경우 \n을 출력한다.
*/