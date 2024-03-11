#include <stdio.h>

int	count_row(char const *s, char traget_char)
{
    int		i;
    int		row_count;
	char	previous_char;

    i = 0;
    row_count = 0;
	previous_char = '\0';
    if (s[i] == '\0')
        return (0);
	if (s[i] != traget_char && s[i])
		row_count++;
	while (s[i])
	{
		if (previous_char == traget_char && s[i])
			row_count++;
		previous_char = s[i];
		i++;
	}
	if (traget_char == '\0')
        row_count = 1;
	return (row_count);
}

int main(void)
{
    char *str = "0c0 eg ghi";
    printf("str: %s\n", str);
    printf("count of row: %d\n", count_row(str, ' '));
}