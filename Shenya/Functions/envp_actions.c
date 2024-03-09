#include "minishell.h"

/* frees the heap envp array from the given position*/
void free_arr(char **env, int len)
{
	int i = 0;

	while (i < len)
	{
		free(env[i]);
		env[i] = NULL;
		i ++;
	}
	free(env);
	env = NULL;
}

/* counts the number of items in envp array */
static int get_len(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i ++;
	return (i);
}

/* Copies the envp array from static memory to heap */
int store_envp(t_envp *vars, char **envp)
{
	int len;
	int i;

	i = 0;
	len = get_len(envp);
	vars->envp = malloc(sizeof(char *) * len + 1);
	if (!vars->envp)
		return (-1);
	vars->envp[len] = NULL;
	while (i < len)
	{
		vars->envp[i] = ft_strdup(envp[i]);
		if (!vars->envp[i])
		{
			free_arr(vars->envp, i);
			return (-1);
		}
		i ++;
	}
	vars->count = len;
	return (0);
}