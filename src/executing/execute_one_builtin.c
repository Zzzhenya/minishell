#include "../../include/minishell.h"

void	exec_one_builtin_cmd(t_cmd *cmd, t_redirec **stdios, t_envp *env, int i)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = 0;
	saved_stdin = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	env->builtin = 1;
	if (setup_redirections(*stdios) == 0)
	{
		clean_stdios_list(stdios);
		if (cmd->r_child->cmdstr[0] != NULL)
			builtin_router(cmd, env, 1, i);
	}
	else
		clean_stdios_list(stdios);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	return ;
}
