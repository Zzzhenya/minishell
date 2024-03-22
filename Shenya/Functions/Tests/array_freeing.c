#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	free_arr(char **arr, int loc)
{
	int i;

	i = 0;
	while (i < loc)
	{
		free (arr[i]);
		arr[i] = NULL;
		i ++;
	}
	free (arr);
	arr = NULL;
}

int main (void)
{
	int i = 0;
	char **arr = NULL;
	arr = (char **)malloc(sizeof(char *) * 5);
	if (!arr)
		return (-1);
	while (i < 5)
	{
		arr[i] = strdup("Hello");
		i ++;
	}
	free_arr(arr, 5);
	return (0);
}