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
void	clean_stdios_list(t_redirec **stdios)
{
	if (*stdios)
	{
		free_stdios(*stdios);
		*stdios = NULL;
	}
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
/*
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
*/
/*
	if (g_exit_status == 2)
		return ; - Probably handled in the parser
*/

pid_t	pipe_and_fork(int *pipefd, t_envp *env, int i)
{
	if (pipe(pipefd) == -1)
		ft_putstr_fd("pipe error\n", 2);
	env->arr[i].pid = fork();
	if (env->arr[i].pid < 0)
		ft_putstr_fd("fork error\n", 2);
	return (env->arr[i].pid);
}

void	parent_process(int *pipefd, int *initial_input,
		t_cmd *cmd, t_redirec **stdios)
{
	install_signals_child();
	write_pipefd(pipefd, initial_input, cmd->pipe_exist);
	clean_stdios_list(stdios);
}

void	child_process(t_redirec **stdios, t_cmd *cmd, t_envp *env, int i)
{
	int				ret;

	ret = 0;
	ret = setup_redirections(*stdios);
	clean_stdios_list(stdios);
	if (ret == 0)
		pid_zero_exec(cmd, env, i);
	else
	{
		env->arr[i].status = 1;
		free_stuff_and_exit(env, 1, i);
	}
}

void	execute_simple_cmd(t_cmd *cmd, t_redirec **stdios, t_envp *env)
{
	int				pipefd[2];
	static int		initial_input = -1;
	int				i;

	i = env->c;
	if (env->procs == 1 && (check_builtin(cmd->r_child, cmd)))
	{
		initial_input = -1;
		exec_one_builtin_cmd(cmd, stdios, env, i);
		return ;
	}
	env->arr[i].pid = pipe_and_fork(pipefd, env, i);
	if (env->arr[i].pid == 0)
	{
		install_signals_main(0);
		setup_pipe_for_child(pipefd, cmd->pipe_exist, initial_input);
		child_process(stdios, cmd, env, i);
	}
	else
	{
		parent_process(pipefd, &initial_input, cmd, stdios);
		env->c ++;
	}
}
