// are there quotes?
//     if outer quotes
//         if outer quotes are single 
//             count single quotes
//                 if count % 2
//                     parsing error
//                 if !(count % 2)
//                     strip all single quotes
//                     do not expand variables
//         if outer quotes are double
//             count double quotes
//                 if count % 2
//                     parsing error
//                 if !(count % 2)
//                     find the next double quote
//                     strip double quote pairs
//                     expand
 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define IN "\"Hello    World\""

char	**ft_splitbyspace(char *str);

int ft_strlen(char *str)
{
    int len = 0;

    if (!str)
        return (len);
    while (str[len] != '\0')
        len ++;
    return (len);
}

int	get_arg_count(char **argv)
{
	int	len;

	len = 0;
	if (!argv || !argv[len])
		return (len);
	while (argv[len])
		len ++;
	return (len);
}

void    print_arr(char **arr)
{
    int i = 0;
    if (!arr || !*arr)
        return ;
    while (arr[i])
    {
        printf("%s\n", arr[i]);
        i ++;
    }
}

void free_arr(char **arr)
{
    int i = 0;
    while (arr[i])
    {
        free (arr[i]);
        i ++;
    }
    free (arr);
}

int string_has_q(char *str, char c)
{
    int i = 0;
    int count = 0;

    while (str[i])
    {
        if (str[i] == c)
            count ++;
        i ++;
    }
    return (count);
}

void    parse(char **arr, int words)
{
    int i = 0;
    int count = 0;

    while (i < words)
    {
        count = string_has_q(arr[i], '\'');
        printf("sq count: %d\n", count);
        count = string_has_q(arr[i], '"');
        printf("dq count: %d\n", count);
        i ++;
    }
}

int main (int argc, char **argv)
{
    char *input;
    char **arr = NULL;
    

    input = NULL;
    (void)argv;
    (void)argc;
    input = malloc(sizeof(char) * ft_strlen(IN) + 1);
    strcpy(input, IN);
    arr = ft_splitbyspace(input);
    argc = get_arg_count(arr);
    printf("words %d\n", argc);
    print_arr(arr);
    parse(arr, argc);
    free_arr(arr);
    //write(1, input, ft_strlen(IN));
    free (input);
    return(0);
}

static int	word_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i ++;
		if (str[i])
			count ++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
	}
	return (count);
}

static char	*ft_copy_string(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	*ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i ++;
	}
	free(arr);
	arr = NULL;
	return (NULL);
}

static char	**intermediate(char *str, char **arr, int start, int k)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		start = i;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
		if (i > start)
		{
			arr[k] = (char *)malloc(sizeof(char) * ((i - start) + 1));
			if (!arr[k])
				return (ft_free_arr(arr));
			ft_copy_string(arr[k], &str[start], i - start);
			k ++;
		}
	}
	arr[k] = NULL;
	return (arr);
}

char	**ft_splitbyspace(char *str)
{
	char	**arr;

	arr = malloc(sizeof(char *) * (word_count(str) + 1));
	if (!arr)
		return (NULL);
	arr = intermediate(str, arr, 0, 0);
	if (!arr)
		return (NULL);
	return (arr);
}