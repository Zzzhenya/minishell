#include "../../include/minishell.h"

int ct_wd_left_rdr(t_parse *checks, const char *str)
{
	if (*(str + 1) == '<')
	{
		str++;
		if (*(str + 1) != '<')
		{
			checks->n_word++;
			checks->inword = 0;
		}
		else
		{
			g_exit_status = 2;
			printf("Syntax error\n");
			return (0);
		}
	}
	else
	{
		checks->n_word++;
		checks->inword = 0;
	}
	return (1);
}

int ct_wd_right_rdr(t_parse *checks, const char *str)
{
	if (*(str + 1) == '>')
	{
		str++;
		if (*(str + 1) != '>')
		{
			checks->n_word++;
			checks->inword = 0;
		}
		else
		{
			g_exit_status = 2;
			printf("Syntax error\n");
			return (0);
		}
	}
	else
	{
		checks->n_word++;
		checks->inword = 0;
	}
	return (1);
}

int ct_wd_rdr_pipe(t_parse *checks, const char *str)
{
	if (*str == '<' && checks->inquote == 0)
	{
		if (!ct_wd_left_rdr(checks, str))
			return (0);
	}
	else if (*str == '>' && checks->inquote == 0)
	{
		if (!ct_wd_right_rdr(checks, str))
			return (0);
	}
	else if (*str == '|' && checks->inquote == 0)
	{
		checks->n_word++;
		checks->inword = 0;
	}
	return (1);
}