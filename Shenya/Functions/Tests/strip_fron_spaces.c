#include <stdio.h>
#include <stdlib.h>

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n')
		return (-1);
	if (c == '\v' || c == '\t')
		return (-1);
	if (c == '\f' || c == '\r')
		return (-1);
	return (0);
}

int ft_strlen(char *str)
{
    int len = 0;

    if (!str)
        return (len);
    while (str[len] != '\0')
        len ++;
    return (len);
}

char	*delete_space_from_str(char *str)
{
	int	i = 0;
	int len = 0;
    char *res;
    int loc = 0;

    res  = NULL;
    if (!str)
        return (NULL);
    while (str[i] != '\0')
    {
        if (ft_isspace(str[i]) == -1)
		    i++;
        else
            break;
    }
    len = ft_strlen(str);
    loc = i;
	res = malloc(sizeof(char) * (len - loc));
	i = 0;
    int new_len = len - loc;
	while (i < new_len)
	{
		res[i] = str[loc];
		i++;
        loc ++;
	}
	return (res);
}

int main(void)
{
    char *str;
    char *ret;

    str = NULL; ret = NULL;
    str = malloc(sizeof(char) * 6);
    str[5] = '\0';
    str[0] = ' ';
    str[1] = 'a';
    str[2] = ' ';
    str[3] = 'b';
    str[4] = ' ';
    printf("str: %s\n", str);
    ret = delete_space_from_str(str);
    printf("ret: %s\n", ret);
    free (ret);
    free (str);
    return (0);
}