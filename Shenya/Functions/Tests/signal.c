#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// cc -Wall -Werror -Wextra -g signal.c -lreadline

void    print_line(int sig)
{
    (void)sig;
    write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line ("", 0);
    rl_redisplay();
}

void    handle(int sig)
{
    (void)sig;
    write (1, "\n", 1);
}

void    install_signal_work(void)
{
    //struct sigaction act1;
    struct sigaction act2;

    //sigemptyset(&act1.sa_mask);
    sigemptyset(&act2.sa_mask);
    //act1.sa_handler = SIG_IGN;
    act2.sa_handler = &handle;//SIG_IGN;
    //sigaction(SIGQUIT, &act1, NULL);
    sigaction(SIGINT, &act2, NULL);
    /*
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);*/
}

void    install_signals_main(void)
{
    //struct sigaction act1;
    struct sigaction act2;

    //sigemptyset(&act1.sa_mask);
    sigemptyset(&act2.sa_mask);
    //act1.sa_handler = SIG_IGN;
    act2.sa_handler = &print_line;
    //sigaction(SIGQUIT, &act1, NULL);
    sigaction(SIGINT, &act2, NULL);
    /*signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, &print_line);*/
}


void    work_loop(void)
{
    pid_t pid;
    int status = 0;
    char **arr = NULL;
    
    arr = (char **)malloc(sizeof(char *) * 2);
    arr[0] = strdup("/bin/cat");
    arr[1] = NULL;
    pid = fork();
    if (pid == -1)
        printf("Fork error\n");
    if (pid == 0)
    {
        install_signals_main();
        if (execve("/bin/cat", arr, NULL) == -1)
        {
            printf("Execve error\n");
            exit(1);
        }
    }
    else
    {
        install_signal_work();
        while (waitpid(-1, &status, WUNTRACED) < 0)
        {

        }
        //printf("status %d\n", status);
        free(arr[0]);
        free(arr);
    }
}

void    input_loop(char *user_input)
{
    while (1)
    {
        signal(SIGQUIT, SIG_IGN);
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
        {
            add_history(user_input);
            work_loop();
        }
        free(user_input);
    }
}

int main (void)
{
    input_loop(NULL);
    return(0);
}