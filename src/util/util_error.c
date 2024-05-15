/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:13:21 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 10:13:22 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	syntax_pipe_error_print(void)
{
	write(2, "syntax error near unexpected token '|'\n",
		ft_strlen("syntax error near unexpected token '|'\n"));
	g_exit_status = 1;
}

char	*delete_space_from_str(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	res = NULL;
	while (str[i] != '\0' && ft_isspace(str[i]) != -1)
		i++;
	len = i;
	res = malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	find_matching_env_row(char *str, char **env)
{
	int		i;
	char	*res;

	i = 0;
	if (str == NULL && *str == '\0')
		return (-1);
	res = delete_space_from_str(str);
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], res, ft_strlen(res)))
			return (i);
		i++;
	}
	free (res);
	return (-1);
}

// char	*trim_single_quotes(char *str)
// {
// 	int		i;
// 	int		len;
// 	char	*res;

// 	i = 0;
// 	len = ft_strlen(str);
// 	res = (char *)malloc((len - 1) * sizeof(char));
// 	if (res == NULL)
// 		return (NULL);
// 	str[len - 1] = '\0';
// 	while (str[i] != '\0')
// 	{
// 		res[i] = str[i + 1];
// 		i++;
// 	}
// 	free(str);
// 	return (res);
// }

// int	remove_single_quotes_from_token(t_data *data, int i)
// {
// 	data->token[i] = trim_single_quotes(data->token[i]);
// 	if (data->token[i] == NULL)
// 		return (-1);
// 	return (0);
// }