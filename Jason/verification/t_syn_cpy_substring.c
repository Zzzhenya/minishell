#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int	ft_strlen(const char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
    int     i;
    char    *res;

    i = 0;
    res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (res == NULL)
        return (NULL);
    while (str[i] != '\0')
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

char	**cpy_substring(char **value, int start, int end)
{
	int		i;
	char	**res;

	res = (char **)malloc((sizeof(char *)) * (end - start + 1));
	if (!res)
		exit(errno);
	i = 0;
	while (i < end - start)
	{
		res[i] = ft_strdup(value[start + i]);
		if (!res[i])
			exit(errno);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	main(void)
{
	char **str = (char **)malloc(sizeof(char *) * 4);
	if (str == NULL)
	{
		printf("fail");
		return (1);
	}
	str[0] = ft_strdup("aaa");
	str[1] = ft_strdup("bbb");
	str[2] = ft_strdup("ccc");
	str[3] = NULL;
	int i = -1;
	while (str[++i])
		printf("str[%d]: %s\n", i, str[i]);
	char **res = cpy_substring(str, 0, 3);
	i = -1;
	while (res[++i])
		printf("res[%d]: %s\n", i, res[i]);
	return (0);
}
