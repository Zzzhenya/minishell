#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char *ret = NULL;

	ret = getenv("PATH");
	if (ret == NULL)
	{
		printf(" :getenv error\n");
		return (1);
	}
	else
	{
		printf("\ngetenv from child: \n\n");
		printf("%s\n", ret);
	}
	return (0);
}