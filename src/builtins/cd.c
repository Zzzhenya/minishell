/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:23:37 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/03 15:23:48 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
int 	chdir(const char *path);

The path argument points to the pathname of a directory.  
The chdir()
     function causes the named directory to become the current working
     directory, that is, 
     the starting point for path searches of pathnames not
     beginning with a slash, ‘/’.
  In order for a directory to become the current directory, a process must
     have execute (search) access to the directory.

RETURN VALUES
     Upon successful completion, a value of 0 is returned.  Otherwise, a value
     of -1 is returned and errno is set to indicate the error.
if (S_ISDIR(statbuf.st_mode))
*/
/*
int	not_a_dir(char	*path)
{
	struct stat	statbuf;

	statbuf.st_mode = 0;
	stat(path, &statbuf);
	if (S_ISREG(statbuf.st_mode))
		return (1);
	else
		return (0);
}

void	print_cd_error(char *path, char *message)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(message, 2);
}*/

char	*change_to_home(t_envp	*my_data)
{
	char	*temp;
	char	*path;
	t_list	*lst;

	temp = NULL;
	path = NULL;
	lst = (my_data->envlist);
	while (lst)
	{
		if (!ft_strncmp((char *)lst->content, "HOME=", ft_strlen("HOME=")))
			temp = (char *)lst->content;
		lst = lst->next;
	}
	if (!temp)
		temp = getenv("HOME");
	while (*temp)
	{
		if (*temp == '/')
		{
			path = ft_strdup(temp);
			break ;
		}
		temp ++;
	}
	return (path);
}

void	execute_path(char	*path, int c, t_envp *my_data)
{
	if (not_a_dir(path))
	{
		my_data->arr[c].status = 1;
		print_cd_error(path, ": Not a directory\n");
		return ;
	}
	else if (chdir(path) == -1)
	{
		my_data->arr[c].status = 1;
		if (errno == EACCES)
			print_cd_error(path, ": Permission denied\n");
		else
			print_cd_error(path, ": No such file or directory\n");
		return ;
	}
	else
	{
		my_data->arr[c].status = 0;
		return ;
	}
}

static char	*get_home_join(t_envp *my_data, char **argv, char *path)
{
	char	*temp;

	temp = NULL;
	temp = change_to_home(my_data);
	path = ft_strjoin(temp, ft_strdup(&argv[1][1]));
	free (temp);
	return (path);
}

void	update_cd_hist(t_envp *my_data, int c)
{
	if (my_data->cd_hist != NULL)
	{
		free(my_data->cd_hist);
		my_data->cd_hist = NULL;
	}
	my_data->cd_hist = get_pwd(my_data, c);
}

void	exec_cd(char **argv, t_envp *my_data, char *path, int c)
{
	if (my_data->cd_hist != NULL && argv[1]
		&& !ft_strncmp(argv[1], "-", ft_strlen(argv[1])))
	{
		path = ft_strdup(my_data->cd_hist);
		ft_putendl_fd(path, 1);
	}
	else if (my_data->cd_hist == NULL && argv[1]
		&& !ft_strncmp(argv[1], "-", ft_strlen(argv[1])))
	{
		path = get_pwd(my_data, c);
		ft_putendl_fd(path, 1);
	}
	else if (argv[1] == NULL || !ft_strncmp(argv[1], "~", ft_strlen(argv[1])))
		path = change_to_home(my_data);
	else if (argv[1][0] == '~' && argv[1][1] == '/')
		path = get_home_join(my_data, argv, path);
	else
		path = ft_strdup(argv[1]);
	update_cd_hist(my_data, c);
	if (my_data->cd_hist == NULL)
		print_cd_error(path, ": error retrieving current directory\n");
	execute_path(path, c, my_data);
	free (path);
}
