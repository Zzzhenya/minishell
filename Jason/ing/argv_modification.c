int		g_exit_status = 0;

/*	[F]
	Put the (c & '\0') to the end of the string.
*/
char	*strjoin_c(char *str, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = 0;
	return (res);
}

/*	[F]
	Same as strjoin_c // param: str, c
	Difference: // param: str, str
*/
char	*strrjoin(char *s1, char *s2)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1)
		return (s2);
	else
	{
		while (s2 && s2[i])
		{
			res = strjoin_c(s1, s2[i]);
			i++;
		}
	}
	return (res);
}

/*	[F]
	if)
	status 13: Permission denied, Should print $?(= 1).
*/
void	if_dollar_ques(char **tmp, char *status, int *flag, int *i)
{
	if (ft_strcmp(status, "13") == 0)
		*tmp = strrjoin(*tmp, "1");
	else
		*tmp = strrjoin(*tmp, status);
	*flag = 1;
	*i += 2;
}

/*	[ ]
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
	Convert integer type of status to the char type.
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

/*
	[Role]
	If specific pattern ("$?") is found in a given string,
	"g_exit_status", stored in the global function is returned.
	= 스트링에서 $?를 발견할 경우 글로벌함수에 저장되어있는 g_exit_status를 리턴.

	[Param]

	[Caution]
	1. ft_itoa use the function 'malloc', should free!!!
	2. Tripple Pointer
		Tripple: ***argv	pointer to address of **argv // &(**argv)
		Double:	 **argv		pointer to address of *argv  // &(*argv)
		Single:  *argv		pointer to address of argv   // &(argv)
		= 삼중 포인터는 주로 2차원 배열 또는 이차원 배열을 함수의 매개변수로 전달할 때 사용됩니다.
		= Triple pointers are mainly used when passing a two-dimensional array
		  as a parameter to a function.

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
		while ((*argv)[i][j] && strjoin_c((*argv)[i], '$') != -1	// no join!! check again.
			&& strjoin_c((*argv)[i], '?') != -1)					// no join!! check again.
		{
			if ((*argv)[i][j] && (*argv)[i][j] == '$'
			&& (*argv)[i][j + 1] == '?')
				if_dollar_ques(&tmp, status, &flag, &j);
			else if ((*argv)[i][j] == '\0')
				break ;
			else
				tmp = strjoin_c(tmp, (*argv)[i][j++]);
		}
		if_tmp(&flag, tmp, &(*argv)[i++]);
		j = 0;
	}
	free(status);
	return ;
}