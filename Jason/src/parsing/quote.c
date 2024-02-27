/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:05:45 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/27 20:12:12 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	[F]
	[Main point]
	validate whether "User_input" has the even number of s_quote and d_quote.
	If it's validated, save the number of sq, dq, which counted, to data struct.

	if(n_sq & n_dq) is 짝수(even number) or 0.
*/
int	count_quote(char *str, t_data *data)
{
	int	i;
	int	n_sq;
	int	n_dq;

	i = 0;
	n_sq = 0;
	n_dq = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			n_sq++;
		if (str[i] == '\"')
			n_dq++;
		i++;
	}
	if (n_sq % 2 == 0 && n_dq % 2 == 0)
	{
		data->n_sq = n_sq;
		data->n_dq = n_dq;
		return (n_sq);
	}
	return (-1);
}

/* [F]
//
// [main point]
//	escaped sequence: Character combination consisting of a backslash.
//		\n = newline
//		\t = tab
//
// [Form]			(1)         (2)
// check_quote_arrangement(tmp_allocated_quote, 0)
// 
// [Param]
//	(1) tmp_allocated_quote[k]
//	(2) Index, which is starting from '0'.
*/
int	check_quote_arrangement(char *str, int i)
{
	int		j;
	char	*m_str;

	j = 0;
	m_str = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (m_str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] != '\'')
			m_str[j++] = str[i++];
		else if (str[i] == '\"' && str[i + 1] != '\"')
			m_str[j++] = str[i++];
		else
			i += 2;
	}
	m_str[j] = '\0';
	if (ft_strlen(m_str) > 3 && m_str[0] == m_str[2] && m_str[0] != '\0')
	{
		free(m_str);
		return (-1);
	}
	if (check_unescaped_quote(m_str) == -1)
		return (-1);
	free(m_str);
	return (0);
}

/* [F]
// 만약 문자열이 비어 있거나
// 유효하지 않은 따옴표 배열을 가지고 있다면 -1 반환 -> 에러.
// Check unescaped quote: ' or " not pair but alone.
*/
int	check_unescaped_quote(char *str)
{
	if (str[0] != '\0')
	{
		if (check_quote_arrangement(str, 0) == -1)
		{
			free(str);
			return (-1);
		}
	}
	return (0);
}

/* [F]
// order_quote(user_input, &data, 0, 0)
//
// Goal
//	Check order of quote
//
// Param(1)
//	user_input // from [func] readline in main.c
//	
// Param(2)
//	typedef struct s_data
//	{
// 		int		word_num;	-> O
// 		int		n_sq;		-> O
// 		int		n_dq;		-> O
//		char	**array;	-> X (Noting saved yet)
//		char	*tmp;		-> O (= user_input)
//	}	t_data;
//
// Param(3, 4) == index.
//	To make the code short below 25 lines.
//
// Example
// 	"ls -la | cat 'abc' -e"
//
// If find \' or \" in str, cpy it to tmp_allocated_quote[k]
//
// tmp_allocated_quote[k] = ["]['][']["][\0]
*/
int	check_quote_order(char *user_input, t_data *data, int i, int k)
{
	char	*tmp_allocated_quote;

	tmp_allocated_quote = malloc((data->n_sq + data->n_dq + 1) * sizeof(char));
	if (tmp_allocated_quote == NULL)
		return (NULL);
	while (user_input[i])
	{
		if (user_input[i] == '\'')
		{
			tmp_allocated_quote[k] = '\'';
			k++;
		}
		else if (user_input[i] == '\"')
		{
			tmp_allocated_quote[k] = '\"';
			k++;
		}
		i++;
	}
	tmp_allocated_quote[k] = '\0';
	if (check_quote_arrangement(tmp_allocated_quote, 0) == -1)
	{
		free(tmp_allocated_quote);
		return (-1);
	}
	free(tmp_allocated_quote);
	return (0);
}

/*  [ main for test ]
int main(void)
{
    int i = -1;
    int res_cqa = 0;
    char *str = "\'\'\"\"\'";
    printf("\nstr: %s\n", str);
    while (str[++i])
        printf("str[i:%d]: %c\n", i, str[i]);
    printf("\n");
    res_cqa = check_quote_arrangement(str, 0);
    printf("\nres_cqa: %d\n", res_cqa);
}
*/
/* sanghun practice
int	check_quotes(char *cmd, int index, int status)
{
	int	i;

	i = index;
	while (cmd[++i] != '\0')
	{
		if (status == 0)
		{
			if (cmd[i] == '\'')
				i = check_quotes(cmd, i, '\'');
			else if (cmd[i] == '\"')
				i = check_quotes(cmd, i, '\"');
			if (i == -1)
				return (1);
			continue ;
		}
		if ((status == '\'') && (cmd[i] == '\''))
			return (i);
		if ((status == '\"') && (cmd[i] == '\"'))
			return (i);
		if (cmd[i + 1] == '\0')
			return (-1);
	}
	if ((status == '\'') || (status == '\"'))
		return (-1);
	return (0);
}

int	parsecmd(char *cmd, t_deque *deque, int debug_mode)
{
	int		i;
	int		margc;
	char	**margv;

	if (check_quotes(cmd, -1, 0))
	{
		ft_putstr_fd("error: Invalid quotation\n", 2);
		return (-1);
	}
	expand_cmd(cmd);
	margc = get_margc(cmd);
	margv = get_margv(cmd, margc);
	cmdtosent(margc, margv, deque);
	if (debug_mode)
	{
		i = 0;
		while (margv[i] != NULL)
			ft_printf("[%s] ", margv[i++]);
		ft_printf("\n");
	}
	i = 0;
	while (margv[i] != NULL)
		free(margv[i++]);
	free(margv);
	return (0);
}

static int	looper(char *cmd, int debug_mode)
{
	int		ret;
	t_sent	*sent;
	t_deque	*deque;

	ret = 0;
	deque = deque_init();
	parsecmd(cmd, deque, debug_mode);
	sent = deque->end;
	if (debug_mode)
	{
		ft_printf("\n");
		sent_print(&sent);
		ft_printf("\n");
		ft_printf("------ result ------\n");
	}
	if (deque->size > 0)
		ret = executecmd(deque);
	sent_delall(&sent);
	deque_del(deque);
	return (ret);
}

static int	looper_wrapper(char *cmd, int debug_mode)
{
	g_sigstatus = 0;
	if (readcmd(cmd, debug_mode) < 0)
		return (-1);
	if (looper(cmd, debug_mode) < 0)
		return (-1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	static int	debug_mode;
	static int	exit_status;
	char		cmd[MAX_COMMAND_LEN];
	t_elst		*lst;

	if (argc > 1 && (ft_strequ(argv[1], "--debug") \
		|| ft_strequ(argv[1], "-d")))
		debug_mode = TRUE;
	else if (argc > 1 && argv)
	{
		ft_putstr_fd("Invalid arguments. Try ./minishell\n", 2);
		return (0);
	}
	signal(SIGCHLD, sigchldhandler);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	lst = env_to_dll(envp);
	start_minishell();
	while (1)
		if (looper_wrapper(cmd, debug_mode) < 0)
			break ;
	exit_status = lst->g_exit;
	env_dellst(lst);
	rl_clear_history();
	return (exit_status);
}
*/

/* rkost practice
int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r' || c == ' ')
		return (TRUE);
	return (FALSE);
}

int	get_margc(char *cmd)
{
	int	i;
	int	cnt;
	int	quote_s;
	int	quote_d;

	i = -1;
	cnt = 0;
	quote_s = 0;
	quote_d = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && quote_d != 1)
			quote_s ^= 1;
		// Bool, toggle (turn on:1 & turn off: 0)
		else if (cmd[i] == '\"' && quote_s != 1)
			quote_d ^= 1;
		// Bool, toggle (turn on:1 & turn off: 0)
		if (quote_s == 0 && quote_d == 0)
		{
			if (!ft_isspace(cmd[i]) && \
				(ft_isspace(cmd[i + 1])
				|| !(cmd[i + 1])
				|| cmd[i + 1] == '|'))
				cnt++;
			else if (cmd[i] == '|')
				cnt++;
		}
	}
	return (cnt);
}

static int	get_nexti(char *s)
{
	int	i;
	int	quote_s;
	int	quote_d;

	i = -1;
	quote_s = 0;
	quote_d = 0;
	while (s[++i])
	{
		if (s[i] == '\'' && quote_d != 1)
			quote_s ^= 1;
		else if (s[i] == '\"' && quote_s != 1)
			quote_d ^= 1;
		if (!quote_s && !quote_d && (ft_isspace(s[i]) || s[i] == '|'))
			break ;
	}
	if (i == 0)
		i++;
	return (i);
}
*/
