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

void   setup_and_run_heredoc(int *token, char  **arr, t_envp *env)
{
    int i = 0;
    int fd = 0;
    int count = 1;
    char *ret = NULL;
    char *name = NULL;
    // int savedin = 0;
    // int savedout = 0;

    //(void)token;
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
                //break; ?? What happens when a heredoc fails in bash????
			    //return (1);
		    }
		    heredoc_input(fd, arr[i+1], env, NULL); // need env for expanding in the heredoc 
		    close(fd);
            count ++;
            free(ret);
            free(arr[i + 1]);
            arr[i + 1] = name;
            //free(name);
		    /*fd = open(HEREDOCNAME, O_RDONLY);
		    dup_and_redirect(fd, STDIN_FILENO);
		    unlink(HEREDOCNAME);*/ // Do this part in the executor but like a normal left redirect 
            //printf("%s\n", arr[i]); // redirection sign
            //printf("%s\n", arr[i+1]); // file name
        }
        i ++;
        token ++;
    }
}