/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:10:59 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/13 21:19:32 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// close, read, write, access, dup, dup2, execve, fork, pipe, unlink
// STDIO_FILENO, STDOUT_FILENO, getcwd, chdir, isatty, ttyname, ttyslot
# include <unistd.h>

// malloc, free, exit, getenv
# include <stdlib.h>

// printf, perror
# include <stdio.h>

// opendir, readdir, closedir
# include <dirent.h>

// open, O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC
# include <fcntl.h>

// errno, EACCES, ENOENT
# include <errno.h>

// strerror
# include <string.h>

// readline
# include <readline/readline.h>

// add_history, clear_history
# include <readline/history.h>

// signal, kill, SIGINT, SIGQUIT, sigaction, sigemptyset, sigaddset
# include <signal.h>

// wait, waitpid, wait3, wait4
# include <sys/wait.h>

// stat, lstat, fstat
# include <sys/stat.h>

// ioctl
# include <sys/ioctl.h>

// tcsetattr, tcgetattr
# include <termios.h>

// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>
# include <term.h>

// @note FLAGS
// STDIN_FILENO == 0
// STDOUT_FILENO == 1
// STDERR_FILENO == 2
# define PIPE_FLAG 3
# define REDI_WR_APPEND_FLAG 4
# define REDI_WR_TRUNC_FLAG 5
# define REDI_RD_FLAG 6
# define HDOC_FLAG 7

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "pipex.h"

#endif
