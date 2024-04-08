#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// cc -Wall -Werror -Wextra -g signal.c -lreadline

void    print_line(int sig)
{
    (void)sig;
    write (1, "SIGQUIT\n", 8);
	rl_on_new_line();
	rl_replace_line ("", 0);
    rl_redisplay();
}

void    install_signal_work(void)
{
    signal(SIGQUIT, &print_line);
}

void    work_loop(char *str)
{
    pid_t pid;
    int i = 0;
    int status = 0;
    
    pid = fork();
    if (pid == 0)
    {
        while (i < 10)
        {
            install_signal_work();
            printf("%s\n", str);
            sleep(1);
            i ++;
        }
    }
    else
    {
        install_signal_work();
        waitpid(-1, &status, WUNTRACED);
        printf("status %d\n", status);
    }
}

void    install_signals_main(void)
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, &print_line);
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