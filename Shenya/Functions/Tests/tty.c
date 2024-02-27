#include <stdio.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/ioctl.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

//char *ttyname(int fd);

/*
The function ttyname() returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd, or NULL on error (for example, if fd is not connected to a
       terminal).  The return value may point to static data, possibly overwritten by the next call.  The function ttyname_r() stores this pathname in the buffer buf of length buflen.

RETURN VALUE
       The function ttyname() returns a pointer to a pathname on success.  On error, NULL is returned, and errno is set appropriately.  The function ttyname_r() returns 0 on success, and an error  num‐
       ber upon error.

*/

int ft_istty(void)
{
	if (isatty(STDIN) && isatty(STDOUT) && isatty(STDERR))
		printf("ISATTY %d\n", errno);
	else
		printf("erno on failure fd==%d,%d,%d: %d\n",STDIN, STDOUT, STDERR, errno);
	if (isatty(5) == 1)
	{
		printf("ISATTY %d\n", errno);
		return (errno);
	}
	else
	{
		printf("erno on failure fd==5: %d\n", errno);
		return (errno);
	}

}

void ft_ttyname(void)
{
	printf("STDIN : %s errno: %d\n", ttyname(STDIN), errno);
	printf("STDOUT: %s errno: %d\n", ttyname(STDOUT), errno);
	printf("STDERR: %s errno: %d\n", ttyname(STDERR), errno);
	printf("fd==3 : %s errno: %d\n", ttyname(3), errno);
	printf("fd==10 : %s errno: %d\n", ttyname(10), errno);

}
/*
int main (void)
{
	printf("initial errno: %d\n", errno);
	ft_istty();
	printf("initial errno: %d\n", errno);
	ft_ttyname();
	printf("final errno: %d\n", errno);
	return (0);
}*/

/* How to test isatty
./a.out
./a.out < cwd.c
*/

int main (void)
{
	int ret;
	char *name;

	name = NULL;
	ret = 0;
	ret = isatty(STDIN);
	printf("ret: 	%d\n", ret);
	printf("errno: 	%d\n", errno);
	name = ttyname(STDIN);
	printf("name: 	%s\n", name);
	printf("errno: 	%d\n", errno);
	if (ret != 1)
		return (errno);
	return (0);
}
