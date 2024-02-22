#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void    print_vals(struct termios *termios_p)
{
    printf("%d\n", termios_p->c_iflag);
    printf("%d\n", termios_p->c_oflag);
    printf("%d\n", termios_p->c_cflag);
    printf("%d\n", termios_p->c_lflag);
    int i = 0;
    while (termios_p->c_cc[i])
    {
        printf("c_cc %d : %d\n",i, termios_p->c_cc[i]);
        i ++;
    }
}

int main(void)
{
    struct termios  termios_p;

    printf("%d\n", tcgetattr(0, &termios_p));
    print_vals(&termios_p);
    printf("%d\n", tcgetattr(1, &termios_p));
    print_vals(&termios_p);
    printf("%d\n", tcgetattr(2, &termios_p));
    print_vals(&termios_p);
    return (0);
}