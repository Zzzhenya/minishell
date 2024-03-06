#include <stdio.h>
#include <stdlib.h>

int ft_strlen(const char *str)
{
    int res;

    res = 0;
    while (str[res])
            res++;
    return (res);
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

int main(void)
{
    char *str = "abcde";
    char *res;
    printf("str: %s\n", str);
    printf("length of str: %d\n", ft_strlen(str));
    res = ft_strdup(str);
    printf("res: %s\n", res);
    return (0);
}