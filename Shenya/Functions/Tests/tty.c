#include <stdio.h>
#include <unistd.h>
#include <sys/errno.h>

//extern int errno;

int main (void)
{
	//extern int errno;
	printf("%d\n", errno);
	if (isatty(0) == 1)
	{
		printf("%d\n", errno);
		printf("ISATTY\n");
	}
	if (isatty(5) == 1)
	{
		printf("%d\n", errno);
		printf("ISATTY\n");
	}
	else
	{
		printf("%d\n", errno);
		return (errno);
	}
	return (0);
}