#include <stdio.h>
#include <unistd.h>
#include <sys/errno.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

//extern int errno;

int main (void)
{
	//extern int errno;
	printf("initial errno: %d\n", errno);
	if (isatty(STDIN) && isatty(STDOUT) && isatty(STDERR))
		printf("ISATTY %d\n", errno);
	else
		printf("erno on failure fd==%d,%d,%d: %d\n",STDIN, STDOUT, STDERR, errno);
	if (isatty(5) == 1)
		printf("ISATTY %d\n", errno);
	else
	{
		printf("erno on failure fd==5: %d\n", errno);
		return (errno);
	}
	return (0);
}