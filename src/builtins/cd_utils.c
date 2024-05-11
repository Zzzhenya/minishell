/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:50:12 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/11 22:20:35 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*get_oldpwd_loc(t_envp *my_data)
{
	t_list	*loc;
	t_list	*curr;

	loc = NULL;
	curr = NULL;
	curr = my_data->envlist;
	while (curr != NULL)
	{
		if (ft_strncmp((char *)curr->content, "OLDPWD=", 7) == 0)
		{
			loc = curr;
			break ;
		}
		curr = curr->next;
	}
	return (loc);
}

void	update_oldpwd(t_envp *my_data, char *pwd)
{
	t_list	*loc;
	char	*join;

	loc = NULL;
	joint = NULL;
	if (pwd == NULL)
		return ;
	join = ft_strjoin("OLDPWD=", pwd);
	free (pwd);
	loc = get_oldpwd_loc(my_data);
	if (loc != NULL)
	{
		free (curr->content);
		curr->content = join;
	}
	else
		ft_lstadd_back(&my_data->envlist, ft_lstnew(join));
}

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
	if (path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd(message, 2);
}
