/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:25:32 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/12 15:25:38 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> //getcwd, chdir, fork, execve, wait, write, read, pipe, dup, dup2, close, isatty, ttyname, ttyslot, unlink
# include <string.h> // strerror, perror
# include <sys/wait.h> // waitpid, wait3, wait4
# include <sys/stat.h> // stat, lstat, fstat, access, open, read, close
# include <fcntl.h> // open, read, close, access
# include <errno.h>
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h> // opendir, closedir, readdir
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcgetattr, tcsetattr
# include <ncurses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

//define el tipo de token
# define T_NULL 0
# define WORD 1
# define PIPE 2
# define REDIR 3
# define DOUBLE_QUOTES 4
# define SINGLE_QUOTES 5

//estructura para un token
typedef struct  s_token 
{

} t_token;

int main();

#endif
