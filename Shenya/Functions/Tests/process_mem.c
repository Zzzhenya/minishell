#include <unistd.h>
#include <stdio.h>
#include <string.h>

void    make_process(char *name)
{
    
}

int main(void)
{
    char *name;

    name = NULL;
    name = strdup("WORD");
    make_process(name);
    return (0);
}