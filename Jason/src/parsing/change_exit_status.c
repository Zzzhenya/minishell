/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:48:21 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 17:48:51 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*	[F]
	
	[Param]
	if_dollar_q_mark(&tmp, exit_status, &flag, &j);
		param(1): &tmp (**tmp)
		param(2): exit_status (*status)
		param(3): &flag	(*flag)
		param(4): &j (*i)

	status 13: Permission denied
		bash에서 status가 13일 경우 터미널에 126 또는 127 중 둘중 하나를 출력.
*/
void	if_dollar_q_mark(char **tmp, char *status, int *flag, int *i)
{
	if (ft_strcmp(status, "13") == 0)
		*tmp = strrjoin(*tmp, "0");
	else
		*tmp = strrjoin(*tmp, status);
	*flag = 1;
	*i += 2;
}

/*	[F]
	argv가 가리키는 대상이 템프(tmp)가 가리키는 대상으로 복사
	Execute when flag is '1' // flag가 1일 때만 실행

	[Progress]
	1. Check 'flag', whether it's '1'
	2. If flag is '1' -> make it to '0'
	3. free (*argv) // Initialize
	4. Duplicate (tmp) to (*argv).
*/
void	if_tmp(int *flag, char *tmp, char **argv)
{
	if (*flag == 1)
	{
		*flag = 0;
		free((*argv));
		(*argv) = ft_strdup(tmp);
	}
	return ;
}

/*	[F]
	Convert integer type of status which got from global variable to ASCII.
	Return type of the value is pointer(char *)
*/
char	*convert_status_to_ascii(void)
{
	char	*status;

	if (g_exit_status == 512)
		status = ft_itoa(2);
	else if (g_exit_status == 256)
		status = ft_itoa(1);
	else
		status = ft_itoa(g_exit_status);
	return (status);
}

/*	[ ]
	[Role]
	If specific pattern ("$?") is found in a given string,
	"g_exit_status", stored in the global function is returned.
	= 스트링에서 $?를 발견할 경우 글로벌함수에 저장되어있는 g_exit_status를 리턴.

	[Caution]
	1. ft_itoa use the function 'malloc', should free!!!
	2. Tripple Pointer
		Tripple: ***argv	pointer to address of **argv // &(**argv)
		Double:	 **argv		pointer to address of *argv  // &(*argv)
		Single:  *argv		pointer to address of argv   // &(argv)
		= 삼중 포인터는 주로 2차원 배열 또는 이차원 배열을 함수의 매개변수로 전달할 때 사용됩니다.
		= Triple pointers are mainly used when passing a two-dimensional array
		  as a parameter to a function.

	[Param]
	replace_exit_status(&validated_token, 0, 0, 0);
		param(1): ***argv = &(validate_token: double pointer)
		param(2): i = 0;
		param(3): flag = 0;
		param(4): j = 0;

	[Progress]
	1. convert_status_to_ascii // convert "g_variable" to "ascii"
	2. tmp = NULL; // Initialize tmp.
	3. 
	4. 
*/
void	replace_exit_status(char ***argv, int i, int flag, int j)
{
	char	*tmp;
	char	*status;

	status = convert_status_to_ascii();
	if ((*argv) == NULL || (**argv) == NULL)
		return ;
	while ((*argv)[i])
	{
		tmp = NULL;
		while ((*argv)[i][j] && f_strchr((*argv)[i], '$') != -1
			&& f_strchr((*argv)[i], '?') != -1)
		{
			if ((*argv)[i][j] && (*argv)[i][j] == '$'
			&& (*argv)[i][j + 1] == '?')
				if_dollar_qu(&tmp, status, &flag, &j);
			else if ((*argv)[i][j] == '\0')
				break ;
			else
				tmp = f_strjoin(tmp, (*argv)[i][j++]);
		}
		if_tmp(&flag, tmp, &(*argv)[i++]);
		j = 0;
	}
	free(status);
	return ;
}
/*
void	replace_exit_status(char ***argv, int i, int flag, int j)
{
	char	*tmp;
	char	*exit_status;
	// i, flag, j == 0
	exit_status = convert_status_to_ascii();
	if ((*argv) == NULL || (**argv) == NULL)
		return ;
	while ((*argv)[i])
	{
		tmp = NULL;
		while ((*argv)[i][j] && ft_strchr_m((*argv)[i], '$') != -1
		// no join!! check again.
			&& ft_strchr_m((*argv)[i], '?') != -1)
		// no join!! check again.
		{
			if ((*argv)[i][j] && (*argv)[i][j] == '$'
			&& (*argv)[i][j + 1] == '?')
				if_dollar_q_mark(&tmp, exit_status, &flag, &j);
			else if ((*argv)[i][j] == '\0')
				break ;
			else
				tmp = strjoin_c(tmp, (*argv)[i][j++]);
		}
		if_tmp(&flagg, tmp, &(*argv)[i++]);
		j = 0;
	}
	free(exit_status);
	return ;
}
*/
