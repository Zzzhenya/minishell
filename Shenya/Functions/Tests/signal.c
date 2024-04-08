#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>

void    work_loop(char *str)
{
    while (1)
    {
        printf("%s\n", str);
    }
}

void    install_signals_main(void)
{
    signal(SIGQUIT, SIG_IGN);
}


void    input_loop(char *user_input)
{
    while (1)
    {
        install_signals_main();
        user_input = readline("Hello > ");
        if (!user_input) // Ctrl + D
        {
            printf("user_input = NULL Ctrl + D\n");
            break;
        }
        /*if (user_input[0] == '\0')
            printf("Enter\n");*/
        if (user_input[0] != '\0')
            add_history(user_input);
        work_loop(user_input);
        free(user_input);
    }
}

int main (void)
{
    input_loop(NULL);
    return(0);
}