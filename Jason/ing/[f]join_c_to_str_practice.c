#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		g_exit_status = 0;

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
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

int	main(void)
{
	char *str = "abcde";
	char *res;
	char c = 'f';
	printf("origin_str: %s\n", str);
	printf("origin_c: %c\n\n", c);
	res = ft_join_c_to_str(str, c);
	printf("res: %s\n", res);
}