#ifndef FORK_H
# define FORK_H

# include <stdio.h>
# include "../../libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

typedef struct s_envp
{
	t_list	*envlist;
	char	**envarr;
	char	*cd_hist;
	int		count;
}	t_envp;

extern int	g_exit_status;	

void 	free_arr(char **env, int len);
void 	unset_one_var(char *var, t_envp *my_data);
void    exec_unset(char **argv, t_envp *my_data);
int 	get_arg_count(char **argv);
void    exec_export(char **argv, t_envp *my_data);
void   export_one_var(char **arr, t_envp *my_data);
void 	rl_replace_line(const char *text, int clear_undo);
void	get_env_var(char *name);
void free_string(void	*input);
void clean_argv(char **argv, int argc);

#endif