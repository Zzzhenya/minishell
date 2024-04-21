#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

typedef  struct s_pipestat
{
	pid_t	pid;
	int 	status;
}	t_pipestat;

void fork_and_child(pid_t pid, t_pipestat *arr, int i)
{
	if (i < 2)
	{
		int ret = 0;
		char **av;

		av = (char **)malloc (sizeof(char *) * 2);
		av[0] = strdup("/bin/cat");
		if (i == 0)
			av[1] = strdup("abc");
		else
			av[1] = strdup("one");
		pid = fork();
		if (pid < 0)
			printf("fork error\n");
		else if (pid == 0)
		{
			ret = execve(av[0], av, NULL);
			if (ret> 0)
			{
				free (av);
				exit (errno);
			}
		}
		if (av) 
			free (av);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			printf("fork error\n");
		else if (pid == 0)
		{
			sleep (i);
			exit (i);
		}
	}
	arr[i].pid = pid;
	waitpid(arr[i].pid, NULL, WNOHANG);
}

void	make_forks(t_pipestat *arr, int count)
{
	int i = 0;

	while (i < count)
	{
		fork_and_child(arr[i].pid, arr, i);
		i ++;
	}
}

void 	wait_forks(t_pipestat *arr, int count)
{
	int i = 0;
	int status;

	while (i < count)
	{
		waitpid(arr[i].pid, &status, 0);
		if (WIFEXITED(status))
			arr[i].status = WEXITSTATUS(status);
		printf("pid: %d , status: %d\n", arr[i].pid, arr[i].status);
		i ++;
	}

}

int main(void)
{
	t_pipestat *arr = NULL;
	int count = 4;
	int i = 0;

	arr = (t_pipestat *)malloc(sizeof(t_pipestat) * count);
	while (i < count)
	{
		arr[i].pid = 0;
		arr[i].status = 0;
		i ++;
	}
	make_forks(arr, count);
	wait_forks(arr, count);
	free (arr);
	return (0);
}
