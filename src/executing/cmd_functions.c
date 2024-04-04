/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:24:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/04/04 14:24:52 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	
	[F]
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

	path_array = envp;
	i = 0;
	while (path_array[i] != NULL)
	{
		if (command[0] != '/')
			path = convert_command_absolute_path(path_array, i, command);
		else
			path = ft_strdup(command);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
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
