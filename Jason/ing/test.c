#include <stdio.h>
#include <stdlib.h>

int		g_exit_status = 0;

int ft_strlen(char *str)
{
    int i;
    while (str[i])
        i++;
    return (i);
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
    printf("7.str: %s\n", str);
	res = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
        printf("8.\n");
		res[i] = str[i];
		i++;
	}
    printf("9.\n");
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
		}
	}
	return (res);
}

void	if_dollar_qu(char **tmp, char *status, int *flag, int *j)
{
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
		free(tmp);
	}
	return ;
}

void	replace_exit_status(char **argv, int i, int flag, int j)
{
	char	*tmp;
	char	*status;

    printf("1.\n");
    status = status_ret();
	if (argv == NULL || *argv == NULL)
		return ;
	status = ft_itoa(g_exit_status);
    printf("1-1. argv[0]: %s\n", argv[0]);
    printf("1-1. argv[1]: %s\n", argv[1]);
    printf("1-1. argv[2]: %s\n", argv[2]);
    printf("1-1. argv[3]: %s\n", argv[3]);
	while (argv[i] != NULL)
	{
        printf("2.\n");
        printf("2-1. argv[%d]: %s\n", i, argv[i]);
		tmp = NULL;
		while (argv[i][j] && ft_strchr_m(argv[i], '$') != -1)
		{
            printf("3.\n");
            printf("3-1. argv[%d]: %s\n", i, argv[i]);
            printf("3-2. argv[%d][%d]: %c\n", i, j, argv[i][j]);
			if (argv[i][j] && argv[i][j] == '$'
			&& argv[i][j + 1] == '?')
            {
                printf("4.\n");
				if_dollar_qu(&tmp, status, &flag, &j);
            }
			else if (!argv[i][j])
            {
                printf("5.\n");
				break ;
            }
			else
            {
                printf("6.\n");
				tmp = ft_join_c_to_str(tmp, argv[i][j++]);
            }
		}
		if_tmp(&flag, tmp, &argv[i++]);
		j = 0;
	}
	free(status);
	return ;
}

int main(void) {
    char **argv = (char **)malloc(4 * sizeof(char *));
    argv[0] = ft_strdup("This is a test string with $? inside");
    argv[1] = ft_strdup("This is another test string without $?");
    argv[2] = ft_strdup("Yet another test string with $?");
    argv[3] = NULL;

    g_exit_status = 123;
    printf("0. g_exit_status: %d\n", g_exit_status);
    replace_exit_status(argv, 0, 0, 0);
    printf("9. g_exit_status: %d\n", g_exit_status);
    for (int i = 0; argv[i] != NULL; ++i)
    {
        printf("%s\n", argv[i]);
        free(argv[i]);
    }
    free(argv);
    return 0;
}

/*
void	replace_exit_status(char **argv, int i, int flag, int j)
{
	char	*tmp = NULL;
	char	*status = ft_itoa(g_exit_status);
    printf("2. status: %s\n", status);
    if (!status)
        return ;
	if (argv == NULL || *argv == NULL)
		return ;
    printf("3.\n");
	while (argv[i] != NULL)
	{
        printf("4.\n");
        int k = 0;
		while (argv[i][j] && ft_strchr_m(argv[i], '$') != -1)
        {
            printf("5.\n");\
			if (argv[i][j] && argv[i][j] == '$'
			&& argv[i][j + 1] == '?')
            {
                printf("6.\n");
				if_dollar_qu(&tmp, status, &flag, &j);
            }
			else
            {
                printf("7.\n");
                char *new_tmp = ft_join_c_to_str(tmp, argv[i][j]);
                free (tmp);
                tmp = new_tmp;
                if (!tmp)
                {
                    free(status);
                    return ;
                }
                j++;
            }
		}
        if (tmp != NULL)
        {
            free(argv[i]);
            argv[i] = tmp;
            flag = 0;
        }
        i++;
        j = 0;
	}
	free(status);
	return ;
}
*/