#include "../../include/minishell.h"

char	*get_oldpwd(char **envp)
{
	char *oldpwd;
	int i = 0;

	oldpwd = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			oldpwd = ft_strdup(&envp[i][ft_strlen("OLDPWD=")]);
		i++;
	}
	return (oldpwd);
}

int	count_procs(t_cmd *tree)
{
	int	count;

	count = 0;
	if (tree == NULL)
		return (0);
	if (tree->node_type == N_SIMPLE_CMD)
		count ++;
	count = count + count_procs(tree->l_child);
	count = count + count_procs(tree->r_child);
	return (count);
}

void	setup_env(t_cmd *tree, t_envp *env)
{
	int i = 0;
	env->cmds = count_commands(tree);
	env->procs = count_procs(tree);
	env->cd_hist = get_oldpwd(env->envarr);
	env->arr = (t_ps *)malloc(sizeof(t_ps) * env->procs);
	while (i < env->procs)
	{
		env->arr[i].pid = 0;
		env->arr[i].status = 0;
		i ++;
	}
}

char	**save_all_env_paths(char **envp, t_envp *env)
{
	int	i;

	i = 0;
	(void)env;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(&envp[i][ft_strlen("PATH=")], ':'));
		i++;
	}
	ft_putstr_fd("No PATH variable in env: Aborting...\n", 2);
	g_exit_status = EXIT_FAILURE;
	//free_things((t_cmd **)NULL, env, NULL, env->user_input);
	// free_stuff_and_exit(env, 1, -1);
	return (NULL);
}
