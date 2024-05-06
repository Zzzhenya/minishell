#include "../../include/minishell.h"

void    heredoc_input(int fd, char *word, t_envp *env, char *line);
/*

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIREC 3
# define T_S_QUOTE 4
# define T_D_QUOTE 5

*/

int stage_heredoc(int fd, char *word, t_envp *env)
{
    pid_t pid = 0;
    int status = 0;
    pid = fork();
    if (pid == 0)
    {
        heredoc_input(fd, word, env, NULL); // need env for expanding in the heredoc
        exit(g_exit_status);
    }
    else
    {
        install_signals_child();
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
        return (g_exit_status);
    }
}

int   setup_and_run_heredoc(int *token, char  **arr, t_envp *env)
{
    int i = 0;
    int fd = 0;
    int count = 1;
    char *ret = NULL;
    char *name = NULL;
    int status = 0;

    while (arr[i])
    {
        if (*token == T_REDIREC && !ft_strncmp(arr[i], "<<", 3))
        {
            ret = ft_itoa(count);
            name = ft_strjoin(HEREDOCNAME, ret);
            fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644); // append the heredoc number to name
		    if (fd == -1)
		    {
			    printf("bash: Too many heredocs\n");
			    g_exit_status = 1;
                free(ret);
                free(name);
                return (1);
		    }
            status = stage_heredoc(fd, arr[i+1], env);
		    close(fd);
            free(ret);
            count ++;
            free(arr[i + 1]);
            arr[i + 1] = name;
            if (status != 0)
            {
                while (count > 0)
                {
                    ret = ft_itoa(count);
                    name = ft_strjoin(HEREDOCNAME, ret);
                    unlink(name);
                    count --;
                    free (ret);
                    free (name);
                }
                return (1);
            }
        }
        i ++;
        token ++;
    }
    return (0);
}