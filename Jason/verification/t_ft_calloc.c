#include <stdio.h>
#include <stdlib.h>

void	*ft_memset(void *dst, int val, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)dst)[i] = val;
		i++;
	}
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	if (count < 1 || size < 1)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, count * size);
	return (tmp);
}

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int main(void)
{
	char *p;
	printf("1. p: %s\n", p);
	printf("1. len of p: %d\n", ft_strlen(p));
	p = calloc(3, 1);
	p = "abcd";
	printf("2. p: %s\n", p);
	printf("2. p: len of p: %d\n", ft_strlen(p));
	return (0);
}
