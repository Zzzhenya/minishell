#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


//char *readline (char *prompt);


int main (void)
{
	char *line = readline ("Enter a line: ");

	printf("User > %s\n", line);
	free (line);
	return (0);
}