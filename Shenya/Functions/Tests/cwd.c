#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>
#include <stdlib.h>

/*char *
     getcwd(char *buf, size_t size);*/

// int main (void)
// {
// 	char *cwd;
// 	int i;

// 	cwd = malloc(sizeof(char) * MAXPATHLEN);
// 	if (!cwd)
// 		return (1);
// 	getcwd(cwd, MAXPATHLEN);
// 	i = strlen(cwd);
// 	cwd[i] = ' ';
// 	cwd[i + 1] = '\0';
// 	printf("%s", cwd);
// 	return (0);
// }