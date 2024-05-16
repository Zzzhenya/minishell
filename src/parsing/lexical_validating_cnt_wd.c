#include "../../include/minishell.h"

int ct_wd_dq(t_parse *checks, const char *str)
{
	if (*(str + 1) == ' ' && (checks->cpy_n_dq % 2 != 0))
	{
		checks->inword = 0;
		checks->inquote = 0;
		checks->prev = 0;
	}
	else if (ft_isalpha(*(str + 1)))
	{
		if (checks->cpy_n_dq % 2 != 0)
		{
			checks->inquote = 0;
			checks->prev = 0;
		}
		else
		{
			checks->inword = 1;
			checks->inquote = 1;
		}
	}
	if (checks->prev != '\'')
		checks->cpy_n_dq--;
	return (0);
}

int ct_wd_sq(t_parse *checks, const char *str)
{
	if (*(str + 1) == ' ' && (checks->cpy_n_sq % 2 != 0))
	{
		checks->inword = 0;
		checks->inquote = 0;
		checks->prev = 0;
	}
	else if (ft_isalpha(*(str + 1)))
	{
		if (checks->cpy_n_sq % 2 != 0)
		{
			checks->inquote = 0;
			checks->prev = 0;
		}
		else
		{
			checks->inword = 1;
			checks->inquote = 1;
		}
	}
	if (checks->prev != '\"')
		checks->cpy_n_sq--;
	return (0);
}

int ct_wd_outquote(t_parse *checks, const char *str)
{
	checks->prev = *str;
	if (*str == '\'')
	{
		if (checks->inword == 0)
			checks->n_word++;
		checks->cpy_n_sq--;
	}
	else if (*str == '\"')
	{
		if (checks->inword == 0)
			checks->n_word++;
		checks->cpy_n_dq--;
	}
	checks->inquote = 1;
	checks->inword = 1;
	return (0);
}

int ct_wd_inquote(t_parse *checks, const char *str)
{
	if (checks->prev != *str)
	{
		if (checks->prev == 0)
		{
			checks->prev = *str;
			checks->n_word++;
			checks->inquote = 1;
			checks->inword = 1;
		}
		else
		{
			if (*str == '\'' && checks->prev != '\"')
				checks->cpy_n_sq--;
			else if (*str == '\"' && checks->prev != '\'')
				checks->cpy_n_dq--;
		}
	}
	else
	{
		if (*str == '\"')
			ct_wd_dq(checks, str);
		else
			ct_wd_sq(checks, str);
	}
	return (0);
}

int ct_wd_else(t_parse *checks)
{
	if (checks->inword == 0)
	{
		checks->n_word++;
		checks->inword = 1;
	}
	return (0);
}