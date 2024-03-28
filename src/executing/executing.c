/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:51:33 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/25 15:56:15 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	[F]
	[Role]
	Find next pipe and update pipe's fd.
	Now each STDIN, STDOUT's fd is changed to initail_input and pipefd[1].

	[Tip]
	1. STDIN_FILENO: Standard macro constants for FD in POSIX. (= 0).
	2. int pipefd[2]
		pipefd[1]:
			FD for writing a file(data) to the 'PIPE'.
			"PARENT PROCESS" send the data as an output to the pipefd[1].

		pipefd[0]:
			FD for reading a file(data) from the 'PIPE'.
			"CHILD PROCESS" gets the data, which paraent sent,
			as an input, from pipefd[0].
	3. dup2
		Param: dup2(oldfd, newfd)
		Return: newfd's number.
		Example: dup2(initial_input, STDIN_FILENO)
				 Initial_input is replaced with STDIN,
				From now on, every input comes only from initial_input.

	[Korean]
	1. 부모 프로세스가 파이프의 쓰기(piepfd[1]) 쪽으로 data를 보내면,
	2. 자식 프로세스는 파이프의 읽기(pipefd[0]) 쪽에서 data를 받는다.

	[Progress]
	1. close(pipefd[0])
		Already read all data from pipefd[0] -> close (파이프의 읽기 측을 닫는 작업)
		= 파이프의 끝을 닫음으로써 데이터가 계속해서 읽히는 것을 방지할 수 있다.
		  파이프를 다음 파이프로 업데이트한다는건,
		  현재 파이프를 통해 데이터를 읽는 과정 끝났다는 소리.
		  현재 파이프를 통해 데이터를 읽는 과정이 완료되었다면,
		  파이프의 읽기 디스크립터를 닫아주는 것이 타당.
		  이로써 해당 프로세스는 파이프로부터의 추가적인 입력을
		  받지 않겠다는 의도를 나타냅니다.
		
		Reason to use
		(1) Prevent "Deadlock".
			If no close, child process try to read data from pipefd[0] infinitely,
			but no more data comes in from Pipe, child may end up waiting infinitely.
		(2) Resource waste (memory and system resource)
			No use -> must close

	2. if (initial_input != -1)
		값이 정상적일 경우 음수는 나올 수 없다.
		그러므로 위 조건은 제대로 된 값이 지정되어있는지를 확인하는 조건문이다.

	3. dup2(initial_input, STDIN_FILENO));
		From now on, “standard input” is received from the FD(= initial_input)
		이제부터 "표준입력"은 initial_input(= FD)에서 받는다.

	4. if (flag_pipe_exist == -1)
		No more pipe token -> close pipefd[1].
	
	5. dup2(pipefd[1], STDOUT_FILENO);
		From now on, “standard output” will be pipefd[1].
		이제부터 "표준출력"은 pipefd[1](= FD)로 한다.
*/
void	update_pipefd(int pipefd[2], int initial_input, int flag_pipe_exist)
{
	close(pipefd[0]);
	if (initial_input != -1)
		(dup2(initial_input, STDIN_FILENO));
	if (flag_pipe_exist == -1)
		close(pipefd[1]);
	else
		dup2(pipefd[1], STDOUT_FILENO);
}

/*	[F]
	Include in "LIBFT".
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return (result);
}

/*	[F]
	[Role]
	Convert cmd to absoulte path, when it has relative path.

	Already used in the project, PIPEX (Verification completed)
*/
char	*convert_command_absolute_path(char **path_array, int i, char *command)
{
	char	*part_path;
	char	*absolute_path;

	part_path = ft_strjoin(path_array[i], "/");
	if (part_path == NULL)
	{
		perror("ft_strjoin: ");
		return (NULL);
	}
	absolute_path = ft_strjoin(part_path, command);
	free(part_path);
	if (absolute_path == NULL)
	{
		perror("ft_strjoin: ");
		return (NULL);
	}
	return (absolute_path);
}

/*	[F]
	[Reference]
		in main.c

	[Under functions]
	1. ft_strncmp	// LIBFT.
	2. ft_split		// LIBFT.
	3. ft_strlen	// LIBFT.
	4. perror		// <stdio.h>
	5. exit			// <stdlib.h>

	Already used in the project, PIPEX (Verification completed)

char	**save_all_env_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(&envp[i][ft_strlen("PATH=")], ':'));
		i++;
	}
	perror("save_all_env_paths: ");
	exit(EXIT_FAILURE);
}*/

/*	[F]
	[Role]
	Compare cmd with paht in ENV.

	[Under functions]
	1. ft_strdup	// LIBFT.
	2. access		// <unistd.h>
	3. free_2d		// util_free.c
	4. free			// <stdlib.h>

	Already used in the project, PIPEX (Verification completed)
*/
char	*check_cmd_in_path(char **envp, char *command)
{
	char	**path_array;
	char	*path;
	int		i;

	//path_array = save_all_env_paths(envp);
	path_array = envp;
	i = 0;
	while (path_array[i] != NULL)
	{
		if (command[0] != '/')
			path = convert_command_absolute_path(path_array, i, command);
		else
			path = ft_strdup(command);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		{
			free_2d(path_array);
			return (path);
		}
		free(path);
		i++;
	}
	free_2d(path_array);
	return (NULL);
}

/*	[F]
	[Role]
	Print errer message about cmd.

	[Under functions]
	1. printf	// <stdio.h>
	2. perror	// <stdio.h>
	3. free		// <stdlib.h>

	Already used in the project, PIPEX (Verification completed)
*/
void	print_error_cmd(t_cmd *file_path, char **envp)
{
	char	*path_buf;

	path_buf = check_cmd_in_path(envp, file_path->cmdstr[0]);
	if (!path_buf)
	{
		printf("%s: ", file_path->cmdstr[0]);
		if (errno != 2)
			perror("");
		else
			printf("command not found\n");
	}
	free(path_buf);
	return ;
}

/*	[F]
	Reference, in "util_str.c"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (*s1 - *s2);
	return (0);
}*/

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
}*/

/*	[F]
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
		Terminates the currently running process, replaces it with another process.
		
		[Key]
		Simular with fork(); but not allocated memory.

		[Form]
		int execve(const char *path, char *const argv[], char *const envp[]);

		[Param]
		(1) *path: path of cmd, that want to execute. (ex) "/bin/ls"
		(2) *argv[]: String include all contents.	  (ex) {"/bin/ls", "-l", NULL}
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
	// Changed based on env struct
	//else if (find_matching_env_row("PATH", envo->envp) != -1)
	//	path_cmd = check_cmd_in_path(env, cmd[0]);
	else if (find_matching_env_row("PATH", envo->envarr) != -1)
		path_cmd = check_cmd_in_path(env, cmd[0]);
	if (!path_cmd)
		exit(2);
	g_exit_status = execve(path_cmd, cmd, env);
	if (path_cmd)
		free(path_cmd);
	g_exit_status = errno;
	if (g_exit_status)
		exit (errno);
}

/*	[F]
	[Role]
	If built-in function -> execute [f] "builtin_action".
	Else external function -> execute [f] "exec". (= system call).

	[progress]
	check_builtin
	1. yes	-> builtin_action
	2. no	-> redirection_error_handle [f]red_error_handle
			-> print error message about cmd.
			-> exec
*/
void	pid_zero_exec(t_cmd *cmd, char **envp, t_envp *env)
{
	/* Function needs to be built - Shenya */
	if (check_builtin(cmd->l_child))
		builtin_action(cmd->r_child, cmd->r_child->cmdstr, env);
	else
	{
		// Function needs to be built
		//temp
		red_error_handle(cmd->l_child, 0);
		print_error_cmd(cmd->l_child, envp);
		exec(cmd->r_child->cmdstr, envp, env);
	}
}

/*	[F]
	[Role]
	파이프의 write fd를 modify하여 데이터를 파이프에 쓰는 과정을 수행.

	[Hint]
	1. PIPE:
		Close write when reading through a pipe,
		and close read when writing through a pipe.
		= 파이프를 통해 읽을때는 쓰기를 닫고, 파이프를 통해 쓸때는 읽기를 닫는다.

	2. Opposite function against [f]update_pipefd.
		[f] update_pipefd
			Close pipefd[0]: FD, is reading a file from the pipe.
			Change STDIN to initial_input and STDOUT to pipefd[1].

		[f] write_pipefd
			Close pipefd[1]: FD, is writing a file to the pipe.
	
	[Progress]
	1. No more need to use Param(2)initial_input -> close.
		Indicates that the current process will not write any more data to the pipe.
		현재 프로세스에서 파이프에 더 이상 데이터를 쓰지 않겠다는 것을 의미.

	2. if (*initial_input != -1)
		If a valid file descriptor is given, close that file descriptor.
		유효한 파일 디스크립터가 주어진다면 해당 파일 디스크립터를 닫.
		= 초기 입력으로 사용된 파일 디스크립터가 더 이상 필요하지 않다.

	3. if (flag_pipe_exist == -1)
		Close the pipe input entrance and set the initial_input value to -1.
		파이프가 더이상 존재하지 않는 경우
		3-1. close(pipefd[0])
			파이프 입력 출입구 닫고,
			현재 프로세스가 더 이상 파이프로부터 데이터를 읽지 않겠다는 것을 의미.
		3-2. initial_input값 -1로 설정 (포인터)
			입력을 나타내는 파일 디스크립터가 더 이상 존재하지 않음.

	4. else
		(if pipe still exist)
		입력으로 pipefd[0]이 파일 디스크립터를 사용할 수 있도록 설정한다.
*/
void	write_pipefd(int pipefd[2], int *initial_input, int flag_pipe_exist)
{
	close(pipefd[1]);
	if (*initial_input != -1)
		close(*initial_input);
	if (flag_pipe_exist == -1)
	{
		close(pipefd[0]);
		*initial_input = -1;
	}
	else
		*initial_input = pipefd[0];
}

/*	[F]
	[Role]
	Find last node among the linked list,
	which contains information of redirections.

	[Progress]
	Until curr points NULL,
	check curr's type and it's < || <<
	If it found, save it to last_redirec.
	Not not found, search next node.
*/
t_redirec	*find_last_in(t_redirec *stdios)
{
	t_redirec	*last_redirec;
	t_redirec	*curr;

	last_redirec = NULL;
	curr = stdios;
	while (curr)
	{
		if (curr->redirec_type == REDIREC_L || curr->redirec_type == REDIREC_LL)
		{
			last_redirec = curr;
		}
		curr = curr->next_redirec;
	}
	return (last_redirec);
}

/*	[F]
	[Role]
	free a pointer to struct of "t_redirec" which has name stdios.

	[Progress]
	1. cpy current struct for t_redirec to (*curr)
	2. while (curr isn't NULL)
		2-1. cpy "curr->next_redirec" to the field for "next" in struct.
		2-2. free (current t_redirec)
		2-3. cpy next to curr. // go to the next node in struct.
*/
/*
Commenting this function out - Already available in src/util/util_free.c

void	free_stdios(t_redirec *stdios)
{
	t_redirec	*curr;
	t_redirec	*next;

	curr = stdios;
	while (curr)
	{
		next = curr->next_redirec;
		free(curr);
		curr = next;
	}
}*/

/*	[F]
	[Role]
	For paraent to wait until the child completes it's execution.
	자식 프로세스가 실행을 완료할 때까지 부모 대기.

	[Progress]
	1. waitpid(-1, &g_exit_status, WNOHANG);
		waitpid (pid_t pid, int *status, int options)
		
		Param(1) -1
			means all child processes.
		Param(2) g_exit_status
			save the result of the status, which is child process was over.
		Param(3) WNOHANG
			Return immediately if no child has exited.
			그냥 기다리면 부모프로세스는 자기가 해야 할 일을 하지 못한채
			자식들이 다 끝나기만을 기다려야 한다.
			그러나 WNOHANG옵션을 사용하게 될 경우,
			부모는 다른 작업을 수행하면서 주기적으로 자식 프로세스의
			종료 여부를 확인할 수 있다.
			만약 자식 프로세스가 종료될 경우 해당 자식 프로세스의
			PID를 반환하고, 종료되지 않았다면 0을 반환한다.
			
			Problem not to use "WNOHANG"
			1. Lower responsiveness
				Blocking, can't do anything only waiting.
				다른 자식 프로세스의 상태를 확인하거나 다른 작업을 수행하는 데 지연이 발생
			2. Deadlock
				자식 프로세스가 종료되지 않는다면, waitpid() 함수는 영원히 블로킹 상태
			3. Waste resource
				부모 프로세스가 자식 프로세스의 종료 여부를 확인하기 위해 CPU 자원을 계속해서 소비
		
	2. find_last_in && find_last_ins == REDIREC_LL
		<<: Input redirection.
		Until no more additional (input redirection) is in node,
			waitpid(): Parent must stop until all children finish,
						and save result to g_exit_status.

	3. else -> free_stdios(*stdios)
		If node is last (REDIRECT), free and also free (2D-free)
*/
void	waiting_child_process(t_redirec **stdios)
{
	waitpid(-1, &g_exit_status, WNOHANG);
	//if (find_last(*stdios, 'l') != NULL
		//&& find_last(*stdios, 'l')->redirec_type == REDIREC_LL)
	if (find_last_in(*(stdios)) != NULL
		&& find_last_in(*(stdios))->redirec_type == REDIREC_LL)
		waitpid(-1, &g_exit_status, 0);
	else
		free_stdios(*stdios);
	*stdios = NULL;
}

/*	[F]
	[Role]
	Execute simple_cmd // 단순 명령어를 실행하는 역할

	[Korean]
	1. 파이프(pipefd) 생성
	2. fork // (parent, child)프로세스를 생성
	3. 자식 프로세스
		3-1. set_signals_interactive
			자식 프로세스에서는 시그널 처리를 설정
		3-2. update_redirfd
			FD number관리하는 update_redirfd 호출
			= 리다이렉션 관련 FD 업데이트
		3-3. update_pipefd
			FD number관리하는 update_pipefd 호출
			= 파이프 관련 FD 업데이트
		3-4. pid_zero_exec
			Execute the function, nevertheless it's built-in or not.
			= 주어진 명령어를 실행하는 함수
			= Built-in && exec(external function)
	4. 부모 프로세스
		4-1. pid_pid_builtin_n_set
			내장 명령어를 처리
		4-2. write_pipefd
			파이프에 데이터를 쓰는 write_pipefd 함수를 호출
		4-3. waiting_child_process
			자식 프로세스가 실행을 완료할 때까지 대기

	[Variable]
	1. pipefd[2]		// Interger array for saving 'FD' for pipe.
	2. initial_input	// Save previous pipe's 'FD'.
	3. PID				// Save process's ID.

	[Struct]
			N_SIMPLE_CMD
			/			\
		(LEFT)			(RIGHT)
	N_FILE_PATH			N_ARGV

	[Progress]
	1. int pipefd[2]	// Declare the variable, pipefd[2], not allocated yet.
	2. pipe(pipefd)		// Make pipe and connect with variabel, pipefd[2].
	3. pid = fork();	// Execute fork function, make child process.
	4. if (pid < 0)		// (pid < 0)means fork function fails.
	5. pid == 0			// Go into child process
		5-1. set_signals_interactive
			Signal handling for what? Shenya.
		5-2. update_redirct
			Check next redirection and update it.
		5-3. update_pipefd
			Check next pipe and update it.
		5-4. pid_zero_exec
			Check whether current function is built-in or not.
		If: built-in function.
			= [f] builtin_action.
		else: Not built-in function.
			= Error [f] red_error_handle.
			= Not redirection -> print error messgae.
			= Execute external function [f] exec (system call)

	6. else (pid > 0)	// Go into parent process
		6-1. pid_pid_builtin_n_set
			Executing buil-in function
		6-2. write_pipefd
			Check pipe and send data to right pipe's output FD.
		6-3. waiting_child_process
			Wait until the child process completes execution.
*/
void	execute_simple_cmd(t_cmd *cmd, t_redirec **stdios, char **envp
		, t_envp *env)
{
	int				pipefd[2];
	static int		initial_input = -1;
	pid_t			pid;

	if (pipe(pipefd) == -1)
		return (perror("pipe: "));
	pid = fork();
	if (pid < 0)
		return (perror("fork: "));
	else if (pid == 0)
	{
		/* Function needs to be built - Shenya*/ 
		//set_signals_interactive(pid);
		update_pipefd(pipefd, initial_input, cmd->pipe_exist);
		setup_redirections(*stdios);
		pid_zero_exec(cmd, envp, env);
	}
	else
	{
		/* Function needs to be built - Shenya*/
		// temp
		pid_pid_builtin_n_set(cmd, env);
		write_pipefd(pipefd, &initial_input, cmd->pipe_exist);
		waiting_child_process(stdios);
	}
}

/*	[F]
	Check the type of redirection and return corresponding int for the redirection.

	[Header file]
	# define REDIREC_R 1	// '>'
	# define REDIREC_RR 2	// '>>'
	# define REDIREC_L 3	// '<'
	# define REDIREC_LL 4	// '<<'

	[Progress]
	1. compare "node->cmdstr[0]" with the macros in headfile.
	2. return the corresponding value with macro.
*/
int	redirect_type(t_cmd *node)
{
	if (ft_strcmp(node->cmdstr[0], "<") == 0)
		return (REDIREC_L);
	else if (ft_strcmp(node->cmdstr[0], "<<") == 0)
		return (REDIREC_LL);
	else if (ft_strcmp(node->cmdstr[0], ">") == 0)
		return (REDIREC_R);
	else if (ft_strcmp(node->cmdstr[0], ">>") == 0)
		return (REDIREC_RR);
	return (0);
}

/*	[F]
	[Role]
	New redirection information is created and added to the list,
	and if information is already in the list,
	new information is added to the end of the existing list.
	
	[Korean]
	새로운 리다이렉션 정보를 생성하여 리스트에 추가,
	이미 리스트에 정보가 있는 경우 기존 리스트의 끝에 새로운 정보 추가

	1. 새로운 t_redirec 구조체에 대한 메모리 할당. (= redirection)
	2. 새로운 리다이렉션 구조체에 필요한 데이터 할당.
		r_child: cmdstr[0]
		l-child: redirect_type.
	3. 만약 stdios 리스트가 비어 있다면(NULL) -> 첫 번째 리다이렉션 정보로 설정
	4. 리스트에 이미 리다이렉션 정보가 있다면,
		현재 리스트 끝까지 이동 후 새리다이렉션 정보 추가.

	[Struct]
			N_SIMPLE_REDIREC
			/				\
		(LEFT)				(RIGHT)
	N_REDIREC_TYPE			N_FILE_NAME

	[Reference]
	typedef struct s_redirec
	{
		int				redirec_type;
		char			*filename;
		struct s_redirec	*next_redirec;
	}	t_redirec;

	typedef struct s_cmd
	{
		struct s_cmd		*l_child;
		struct s_cmd		*r_child;
		char				**cmdstr;
		int					node_type;
		int					flag_pipe_exist;
		int					pre_flag;
	}	t_cmd;

	[Progress]
	1. Allocate memory (t_redirec) for redirection.
	2. Put all data about new redirection
		to the new struct(= "redirection"), made in 1st step.
	3. Check whether current redirect is first or not.
		(리다이렉션 정보가 첫 번째인지 여부를 확인)
		3-1. if first
			cpy redirection to *stdios.
		3-2. else
			curr is *stdios.
			track the end of *stdios.
			When meet with end of redirec -> add redirection to the end of *stdios.
*/
void	execute_simple_redirect(t_cmd *node, t_redirec **stdios)
{
	t_redirec	*redirection;
	t_redirec	*curr;

	redirection = (t_redirec *)malloc(sizeof(t_redirec));
	if (redirection == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	redirection->filename = node->r_child->cmdstr[0];
	redirection->redirec_type = redirect_type(node->l_child);
	redirection->next_redirec = NULL;
	if (*stdios == NULL)
		*stdios = redirection;
	else
	{
		curr = *stdios;
		while (curr->next_redirec)
			curr = curr->next_redirec;
		curr->next_redirec = redirection;
	}
}

/*	[F]
	[Role]
	Check the NODE'S TYPE, execute next tree node,
	corresponding to the certain node type.

	[Korean]
	1. 트리의 노드를 실행.
	2. 노드타입에 따라 각기 다른 동작 수행.
	3. 간단명령: execute_simple_cmd 함수호출.
	4. 리다이렉션: execute_simple_redirect 함수호출.

	[Available types for cild_node]
	1. N_SIMPLE_CMD
		LEFT: file_path
		RIGHT: argv
	2. N_SIMPLE_REDIREC
		LEFT: type
		RIGHT: file_name

	[Progress]
	1. If node's type == (N_CMD, N_REDIREC)
		= "there are more redirects and pipes that need to be handled first."
		= return ; // nothing happen.

	2. If node's type == (N_SIMPLE_CMD)
		execute_simple_cmd

	3. If node's type == (N_SIMPLE_REDIREC)
		execute_simple_redirect

	[Struct]
						  N_CMD(1)			|			N_CMD(2)
					/				\
			N_REDIREC				N_SIMPLE_CMD
			/		\					/			\
	N_REDIREC	N_SIMPLE_REDIREC	N_FILE_PATH		N_ARGV
					/		\
		N_REDIREC_TYPE		N_FILE_NAME

*/
void	execute_tree(t_cmd *node, t_redirec **stdios, char **envp, t_envp *envs)
{
	if (node->node_type == N_CMD || node->node_type == N_REDIREC)
		return ;
	else if (node->node_type == N_SIMPLE_CMD)
		execute_simple_cmd(node, stdios, envp, envs);
	else if (node->node_type == N_SIMPLE_REDIREC)
		execute_simple_redirect(node, stdios);
}

/*	[F]
	[Role]
	It receives a parsed tree, traverses that tree struct,
	executres cmds and handles file redirection and pipes.

	[Korean]
	1. 파싱된 트리를 받아 순회하며 명령 실행 & 리다이렉션 처리.
	2. 트리 각 노드를 방문 -> 각 노드 타입 확인 -> 적절한 동작 수행.
	3. 바로 실행 가능한 노드인지 체크, 가능하다면 실행.
	4. 자식 노드 있다면 해당 자식 노드 방문.

	[Key]
	Order: left-first traversal
	To process the left child node first -> and then the right child node.

	[Struct]
						  N_CMD
					/				\
			N_REDIREC				N_SIMPLE_CMD
			/		\					/			\
	N_REDIREC	N_SIMPLE_REDIREC	N_FILE_PATH		N_ARGV
					/		\
		N_REDIREC_TYPE		N_FILE_NAME

	[Progress]
	1. "execute_tree"
		If meet with nodes, still have more child nodes,
			skip node, cause can't execute now.
		
		(if) curr node is (CMD) or (REDIRECTS)
			= Skip to the next node, cause current node couldn't be executed.

		(else) curr node is (N_SIMPLE_CMD) or (N_SIMPLE_REDIREC)
			= Execute node right away, cause it could be executed.

	2. if (left child's node_type != SIMPLE_CMD, SIMPLE_REDIREC)
		There is more nodes from l_child's node
		= search more about l_child node.

	3. if (right child's node_type != SIMPLE_CMD, SIMPLE_REDIREC)
		There is more nodes from r_child's node
		= search more about r_child node.
*/
void	search_tree(t_cmd *node, char **envp, t_envp *env)
{
	static t_redirec	*stdios;

	if (node == NULL)
		return ;
	execute_tree(node, &stdios, envp, env);
	if (node->l_child && (node->l_child->node_type != N_REDIREC_TYPE
			|| node->l_child->node_type != N_FILE_PATH))
		search_tree(node->l_child, envp, env);
	if (node->r_child && (node->r_child->node_type != N_FILE_NAME
			|| node->r_child->node_type != N_ARGV))
		search_tree(node->r_child, envp, env);
}

/*	[F]
	Reference
	1. Validate input and convert it to token.
	2. Input is divided based on the pipe(|).
	3. returned in the form of a tree for token.

t_cmd	*parse_user_input(char *user_input, t_envp *env)
{
	t_cmd	*cmd_tree;
	char	**validated_input;
	int		*token;
	int		token_sequence[2];
	int		tmp;

	if (user_input == NULL || user_input[0] == 0)
		return (NULL);
	cmd_tree = NULL;
	//validated_input = validate_input(user_input, env->envp);
	validated_input = validate_input(user_input, env->envarr);
	if (!validated_input)
		return (NULL);
	replace_exit_status(&validated_input, 0, 0, 0);
	token = token_malloc(validated_input);
	if (!token)
		return (NULL);
	token_sequence[0] = 0;
	token_sequence[1] = check_token_length(token);
	tmp = syntax_pipe(validated_input, token, token_sequence, &cmd_tree);
	if (tmp == -1)
		free_tree(cmd_tree);
	if (tmp == -1)
		return (NULL);
	free_2d(validated_input);
	free(token);
	return (cmd_tree);
}*/

/*	[F]
	[Example]
	1. *tree = parse_user_input(user_input, env);
					P
			R				W
		W		R		W		R
			W		W				W
	= Already seperated to tokens.

	2. search_tree(*tree, envp, env);
	= Check node's status and decide the direction (left || right).

	3. Follow tree and execute corresponding nodes.

	4. No more tree to execute (= finish to search tree)
		-> free_tree(tree)
		-> free_2d(user_input)

void	non_interactive_mode(t_cmd **tree,
								char *input, char **envp, t_envp *env)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(input, ';');
	i = 0;
	while (user_inputs[i])
	{
		*tree = parse_user_input(user_inputs[i], env);
		search_tree(*tree, envp, env);
		i++;
		free_tree(*tree);
	}
	free_2d(user_inputs);
}
*/