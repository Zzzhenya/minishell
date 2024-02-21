#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main(void)
{
	char *input;
	
	input = readline("Enter a command: ");
	//printf("You entered: %s\n", input);
	//free(input);
	return 0;
}
