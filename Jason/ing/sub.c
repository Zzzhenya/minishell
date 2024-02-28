#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		g_exit_status = 0;

int ft_strlen(char *str)
{
    int i;
    while (str[i])
        i++;
    return (i);
}

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

char	*ft_strdup(char *src)
{
	size_t	i;
	size_t	len;
	char	*p;

	i = 0;
	len = ft_strlen(src);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static int	ft_get_len(int number)
{
	int	length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		length++;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

char	*ft_convert_int_to_str(int n, int length)
{
	long	number;
	char	*result;

	number = n;
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (NULL);
	if (number < 0)
	{
		result[0] = '-';
		number = -number;
	}
	if (number == 0)
		result[0] = '0';
	result[length--] = '\0';
	while (number != 0)
	{
		result[length] = number % 10 + '0';
		length--;
		number /= 10;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		length;
	char	*result;

	length = ft_get_len(n);
	result = ft_convert_int_to_str(n, length);
	return (result);
}

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

char	*ft_join_c_to_str(char *str, char c)
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
			res = ft_join_c_to_str(s1, s2[i]);
			i++;
            return (res);
		}
	}
	return (NULL);
}

void	if_dollar_qu(char **tmp, char *status, int *flag, int *j)
{
	if (ft_strcmp(status, "13") == 0)
		*tmp = strrjoin(*tmp, "0");
	else
		*tmp = strrjoin(*tmp, status);
	*flag = 1;
	*j += 2;
}

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

char	*status_ret(void)
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

void	replace_exit_status(char ***argv, int i, int flag, int j)
{
	char	*tmp;
	char	*status;

	status = status_ret();
	if ((*argv) == NULL || (**argv) == NULL)
		return ;
	while ((*argv)[i])
	{
		tmp = NULL;
		while ((*argv)[i][j] && ft_strchr_m((*argv)[i], '$') != -1
			&& ft_strchr_m((*argv)[i], '?') != -1)
		{
			if ((*argv)[i][j] && (*argv)[i][j] == '$'
			&& (*argv)[i][j + 1] == '?')
				if_dollar_qu(&tmp, status, &flag, &j);
			else if ((*argv)[i][j] == '\0')
				break ;
			else
				tmp = ft_join_c_to_str(tmp, (*argv)[i][j++]);
		}
		if_tmp(&flag, tmp, &(*argv)[i++]);
		j = 0;
	}
	free(status);
	return ;
}

int main()
{
    char **argv = (char **)malloc(4 * sizeof(char *));
    argv[0] = ft_strdup("command");
    argv[1] = ft_strdup("arg1");
    argv[2] = ft_strdup("arg$?");
    argv[3] = NULL;

    g_exit_status = 512;

    printf("Before replacement:\n");
    for (int i = 0; argv[i]; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    replace_exit_status(&argv, 0, 0, 0);

    printf("After replacement:\n");
    for (int i = 0; argv[i]; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    for (int i = 0; argv[i]; i++){
        free(argv[i]);
    }
    free(argv);
    return 0;
}