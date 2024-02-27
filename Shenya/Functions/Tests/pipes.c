#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int     fd[2];
    pid_t   pid;

    if (pipe(fd) == -1)
        printf("Pipe() error\n");
    pid = fork();
    if (pid == -1)
        printf("fork() error\n");
    else if (pid == 0)
        child_process();
    else
    {
        waitpid(pid,NULL, WNOHANG);
        parent_process();
    }
    return(0);
}