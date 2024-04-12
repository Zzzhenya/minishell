/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:37:59 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/04 15:05:26 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	[F]
	Reference, in "lexical_expanding.c"
	Search Param(1): "str" from
	Param(2): "env", which number of line does it in ENV.


int	find_matching_env_row(char *str, char **env)
{
	int	i;

	i = 0;
	if (str == NULL && *str == '\0')
		return (-1);
	while (env[i] != NULL)
	{
		if (ft_strcmp(env[i], str) != -1)
			return (i); 
		i++;
	}
	return (-1);
}

	[F]
	[Role]
	Execute all function, which is in the env's paths, except built-in.

	[Form]
	exec(cmd->r_child->cmdstr, envp, env);

	[Param]
	(1) cmdstr: Value of "cmdstr" of r_child,
				is right side leaf node from curr node.
	(2) envp: Struct from main.c (환경 변수)
	(3) envo: Must discuss with Shenya, whether we need this.
			  (환경 변수들을 가리키는 구조체)
	
	[Tipp]
	1. execve
	
		[Role]
		Terminates the currently running process, 
		replaces it with another process.
		
		[Key]
		Simular with fork(); but not allocated memory.

		[Form]
		int execve(const char *path, char *const argv[], char *const envp[]);

		[Param]
		(1) *path: path of cmd, that want to execute. (ex) "/bin/ls"
		(2) *argv[]: String include all contents.	  
			(ex) {"/bin/ls", "-l", NULL}
		(3) *envp[]: Which env does want to use for executing this process.

		[Return]
		1. Success:	 X
			execve가 성공했다는건 새로운 프로세스가 실행됐다는 의미다.
			당연히 기존 process의 return은 안보이는게 정상이다.
		2. Fail:	-1

	[Progress]
	1. cmd, cmd[0] == NULL
		Nothing to execute -> exit(0).

	2. path = NULL
		initialization for the "path" pointer.

	3. if (access(cmd[0], X_OK))
		Check the access rights to the file, if it is executable
		= OK -> cpy cmd[0] to "path_cmd".

	4. else if
		No rights to execute -> Search PATH of "env".
		= OK -> cpy the path of cmd[0] from "PATH ENV" to "path_cmd".
		PATH 디렉토리들을 검색하고, 실행 가능한 경우 해당 경로를 path에 저장.

	5. if (!path_cmd)
		[f] check_cmd_in_paht fails -> error
			= 실행할 수 있는 명령어가 없다면, exit(2): error code "2".

	6. execve(path_cmd, cmd, env)
		execute "path_cmd" !!
	
	7. if (path_cmd)
		This conditional statement is executed only
		,when the execve function fails.
		이 조건문이 실행됐다는건, execve함수가 실패할때만 가능하다.
		= free(path_cmd)
		= errno(for EXIT)
		   when errer happens in system call of library function.
			update errno code and save it to 'g_exit_status'.
	cmd = strip_empty_strings(cmd);
*/

void	exec(char **cmd, char **env, t_envp *envo)
{
	char	*path_cmd;
	int		g_exit_status;

	if (!cmd || !cmd[0])
		exit(0);
	path_cmd = NULL;
	if (access(cmd[0], X_OK) == 0)
		path_cmd = cmd[0];
	else if (find_matching_env_row("PATH", envo->envarr) != -1)
		path_cmd = check_cmd_in_path(env, cmd[0]);
	if (!path_cmd)
	{
		g_exit_status = 2;
		free_stuff_and_exit(envo, 1);
	}
	g_exit_status = execve(path_cmd, cmd, envo->envarr);
	if (path_cmd)
		free(path_cmd);
	g_exit_status = errno;
	if (g_exit_status)
		//exit (errno);
		free_stuff_and_exit(envo, 1);
}

/*	[F]
	[Role]
	If built-in function -> execute [f] "builtin_action".
	Else external function -> execute [f] "exec". (= system call).

	[progress]
	check_builtin
	1. yes	-> builtin_router
	2. no	-> redirection_error_handle [f]red_error_handle
			-> print error message about cmd.
			-> exec
*/
void	pid_zero_exec(t_cmd *cmd, char **envp, t_envp *env, pid_t pid)
{
	if (check_builtin(cmd->l_child))
		builtin_router(cmd, env, pid);
	else
	{
		redirection_error_handle(cmd->l_child, pid);
		print_error_cmd(cmd->l_child, envp);
		exec(cmd->r_child->cmdstr, envp, env);
	}
}
