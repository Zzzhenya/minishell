#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int	check_unescaped_quote(char *str)
{
    printf("2. in check_unescaped_quote function\n");
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
        printf("str[i:%d]: %c\t", i, str[i]);
        printf("str[i:%d]: %c\n", i+1, str[i+1]);
		if (str[i] == '\'' && str[i + 1] != '\'')
			m_str[j++] = str[i++];
		else if (str[i] == '\"' && str[i + 1] != '\"')
			m_str[j++] = str[i++];
		else
			i += 2;
        printf("m_str[j:%d]: %c\n", j - 1, m_str[j-1]);
        printf("i: %d, j: %d\n\n", i, j);
	}
	m_str[j] = '\0';
    printf("1. m_str: %s\n", m_str);
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

/* From sanghun.
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

/* From rkost
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
			quote_s ^= 1;						// Bool, toggle (turn on:1 & turn off: 0)
		else if (cmd[i] == '\"' && quote_s != 1)
			quote_d ^= 1;						// Bool, toggle (turn on:1 & turn off: 0)
		if (quote_s == 0 && quote_d == 0)
		{
			if (!ft_isspace(cmd[i]) && \
				(ft_isspace(cmd[i + 1]) || !(cmd[i + 1]) || cmd[i + 1] == '|'))
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