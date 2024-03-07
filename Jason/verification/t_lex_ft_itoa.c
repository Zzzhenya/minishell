#include <stdio.h>
#include <stdlib.h>

int		g_exit_status = 0;

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

int	main(void)
{
	printf("g_exit_status: %d\n", g_exit_status);
    printf("itoa(g_exit_status): %s\n", ft_itoa(g_exit_status));
}