#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd = 0;

    if (isatty(fd) != '\0')
        printf("File descriptor %d is connected to a terminal.\n", fd);
    else
        printf("File descriptor %d is not connected to a terminal.\n", fd);
    return 0;
}
