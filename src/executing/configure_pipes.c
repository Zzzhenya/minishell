/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:44:19 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/09 13:44:21 by sde-silv         ###   ########.fr       */
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
/*
	In the child process

	close the read end of the pipe
	if the child is not the first process of the pipeline (initial input != -1)
		duplicate the fd stored in initial_input to STDIN
	if at the end of pipeline (pipe_exist == -1)
		close write end of pipe
	else (not at the end of pipeline)
		duplicate the write end of pipe to stdout

	initial_input is used to find whether we are at the start of pipeline.
	the fd of read_end of the previous pipe saved in initial input is
	duplicated to STDIN to link the new pipe to the old pipe
*/

void	setup_pipe_for_child(int *pipefd, int pipe_exist, int initial_input)
{
	close(pipefd[0]);
	if (initial_input != -1)
		dup2(initial_input, STDIN_FILENO);
	if (pipe_exist == -1)
		close(pipefd[1]);
	else
		dup2(pipefd[1], STDOUT_FILENO);
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

/*
	In the parent process
	
	close the write end of the pipe
	if the child is not the first process of the pipeline (initial input != -1)
		close the fd stored in initial_input from last process
	if at the end of pipeline (pipe_exist == -1)
		close read end of pipe
		reset initial_input to -1 for the next pipeline
	else (not at the end of pipeline)
		save fd of read end of pipe in initial_input

	initial_input is used to find whether we are at the start of pipeline
	and also to store the fd of read end of the last pipe in the pipeline
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
