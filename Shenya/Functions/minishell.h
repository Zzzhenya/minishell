#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
/* READLINE includes + flags in Makefile */
# include <readline/readline.h>
# include <readline/history.h>
/* execve fork chdir getcwd*/
# include <unistd.h>
/* wait wait2 wait3*/
# include <sys/wait.h>
#if __linux__ 
# include <sys/errno.h>
#else
# include <errno.h>
#endif
# include <limits.h>
# include "libft/libft.h"

#ifndef PATH_MAX
# define PATH_MAX 2048
#endif

# define EX_CMD_NOT_FOUND 127

typedef struct s_envp
{
	char	**envp;
	char	*cd_hist;
}	t_envp;

extern int	g_exit_status;

char	**ft_splitbyspace(char *str);

int get_arg_count(char **argv);

void	get_env_var(char *name);

int run_command(char **argv);

int run_command1(char *cmd, char **argv);

void clean_argv(char **argv, int argc);

/* Built-ins*/
//void	exec_builtin(char **argv);
void	exec_builtin(char **argv, t_envp *my_data);

/* builtins/pwd.c */
void	exec_pwd(void);
char	*get_pwd(void);

/* builtins/cd.c */
//void    exec_cd(char **argv);
void    exec_cd(char **argv, t_envp *mydata);

/* builtins/env.c */
void	exec_env(char **argv, t_envp *my_data);

/* builtins/echo.c */
void	exec_echo(char **argv);

#endif