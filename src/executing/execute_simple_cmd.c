/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:25:03 by tkwak             #+#    #+#             */
/*   Updated: 2024/04/10 16:27:10 by sde-silv         ###   ########.fr       */
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
			If no close, child process try to read data
			 from pipefd[0] infinitely,
			but no more data comes in from Pipe, child 
			may end up waiting infinitely.
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
// void	update_pipefd(int pipefd[2], int initial_input, int flag_pipe_exist)
// {
// 	(void)initial_input;
// 	if (flag_pipe_exist == -1)
// 		close(pipefd[1]);
// 	else
// 		dup2(pipefd[1], STDOUT_FILENO);
// }

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
		Indicates that the current process will not write 
		any more data to the pipe.
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
	if (find_last_in(*(stdios)) != NULL
		&& find_last_in(*(stdios))->redirec_type == REDIREC_LL)
*/
void	waiting_child_process(t_redirec **stdios, pid_t pid)
{
	(void)pid;
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
		free_stdios(*stdios);
		*stdios = NULL;
		if (cmd->r_child->cmdstr[0] != NULL)
			builtin_router(cmd, env, 1, i);
	}
	else
	{
		free_stdios(*stdios);
		*stdios = NULL;
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	return ;
}

void	setup_pipe_for_child(int *pipefd, int pipe_exist, int initial_input)
{
	close(pipefd[0]);
	if (pipe_exist != -1)
		dup2(initial_input, STDIN_FILENO);
	if (pipe_exist == -1)
		close(pipefd[1]);
	else
		dup2(pipefd[1], STDOUT_FILENO);
}

void	execute_simple_cmd(t_cmd *cmd, t_redirec **stdios, t_envp *env)
{
	int				pipefd[2];
	static int		initial_input = -1;
	int				i;
	int				ret;

	ret = 0;
	i = env->c;
	if (env->procs == 1 && (check_builtin(cmd->r_child, cmd)))
	{
		initial_input = -1;
		exec_one_builtin_cmd(cmd, stdios, env, i);
		return ;
	}
	if (g_exit_status == 2)
		return ;
	if (pipe(pipefd) == -1)
		return (perror("pipe: "));
	env->arr[i].pid = fork();
	if (env->arr[i].pid < 0)
		return (perror("fork: "));
	else if (env->arr[i].pid == 0)
	{
		install_signals_main(0);
		setup_pipe_for_child(pipefd, cmd->pipe_exist, initial_input);
		ret = setup_redirections(*stdios);
		if (*stdios)
		{
			free_stdios(*stdios);
			*stdios = NULL;
		}
		if (ret == 0)
			pid_zero_exec(cmd, env, i);
		else
		{
			env->arr[i].status = 1;
			free_stuff_and_exit(env, 1, i);
		}
	}
	else
	{
		install_signals_child();
		write_pipefd(pipefd, &initial_input, cmd->pipe_exist);
		waiting_child_process(stdios, env->arr[i].pid);
		env->c ++;
	}
}
