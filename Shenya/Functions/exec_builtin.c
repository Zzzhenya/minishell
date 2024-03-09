#include "minishell.h"

//extern int  g_exit_status;
/*
man bash

 EXIT STATUS
       The exit status of an executed command is the value returned by the  waitpid  system  call  or  equivalent
       function.   Exit  statuses  fall  between  0 and 255, though, as explained below, the shell may use values
       above 125 specially.  Exit statuses from shell builtins and compound commands are  also  limited  to  this
       range.  Under certain circumstances, the shell will use special values to indicate specific failure modes.

       For  the shell's purposes, a command which exits with a zero exit status has succeeded.  An exit status of
       zero indicates success.  A non-zero exit status indicates failure.  When a command terminates on  a  fatal
       signal N, bash uses the value of 128+N as the exit status.

       If  a command is not found, the child process created to execute it returns a status of 127.  If a command
       is found but is not executable, the return status is 126.

       If a command fails because of an error during expansion or redirection, the exit status  is  greater  than
       zero.

       Shell  builtin commands return a status of 0 (true) if successful, and non-zero (false) if an error occurs
       while they execute.  All builtins return an exit status of 2 to indicate incorrect  usage,  generally  in‐
       valid options or missing arguments.

       Bash  itself  returns the exit status of the last command executed, unless a syntax error occurs, in which
       case it exits with a non-zero value.  See also the exit builtin command below.

       pwd [-LP]
              Print  the  absolute  pathname  of the current working directory.  The pathname printed contains no
              symbolic links if the -P option is supplied or the -o physical option to the set builtin command is
              enabled.   If  the  -L option is used, the pathname printed may contain symbolic links.  The return
              status is 0 unless an error occurs while reading the name of the current directory  or  an  invalid
              option is supplied.


PATH_MAX is defined in limits.h


void	exec_pwd(void)
{  
	char *buf;

    buf = NULL;
	buf = getcwd(buf, PATH_MAX);
	if (!buf)
        exit(EXIT_CMD_NOT_FOUND);
    else
	{
		printf("%s\n", buf);
		free (buf);
	}
}
*/

void	exec_builtin(char **argv, t_envp *my_data)
{
	if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
		exec_pwd();
	else if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
		exec_cd(argv, my_data);
    else if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
        exec_env(argv, my_data);
    else if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
        exec_echo(argv);
    else if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
        exec_export(argv, my_data);
    else if (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])))
        exec_unset(argv, my_data);
	else
		printf("%s\n", argv[0]);
}