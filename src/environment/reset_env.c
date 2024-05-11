#include "../../include/minishell.h"

void	free_things(t_cmd **tree, t_envp *env, char **envp, char *user_input)
{
	if (*tree)
		free_tree(*tree);
	if (env->envarr)
		free_arr(env->envarr, get_arg_count(env->envarr));
	if (envp)
		free_2d(envp);
	if (user_input)
	{
		free (user_input);
		user_input = NULL;
	}
	if (env->arr)
	{
		free (env->arr);
		env->arr = NULL;
	}
	if (env->cd_hist != NULL)
	{
		free (env->cd_hist);
		env->cd_hist = NULL;
	}
	env->procs = 0;
	env->c = 0;
	env->cmds = 0;
	env->builtin = 0;
}
