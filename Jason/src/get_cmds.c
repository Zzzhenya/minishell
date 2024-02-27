/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_a_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:12:24 by subpark           #+#    #+#             */
/*   Updated: 2024/02/12 15:01:27 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* [ ]
// main.c
// parse_user_input(user_input, env);
//
*/
t_cmd	*parse_user_input(char *user_input, t_envp *env)
{
	t_cmd	*cmd_tree;
	char	**validated_input;
	int		*token;
	int		i[2];
	int		tmp;

	if (user_input == NULL || user_input[0] == 0)
		return (NULL);
	cmd_tree = NULL;											// Initiailzing cmd_tree struct
	validated_input = validate_input(user_input, env->envp);	// Copy all values from "user_input" to "t_data struct".
	if (!validated_input)
		return (NULL);
	replace_exit_status(&validated_input, 0, 0, 0);				// Handling $, &, 
	token = token_data(validated_input);
	if (!token)
		return (NULL);
	i[0] = 0;
	i[1] = token_length(token);
	tmp = syntax_pipe(validated_input, token, i, &cmd_tree);
	if (tmp == -1)
		free_tree(cmd_tree);
	if (tmp == -1)
		return (NULL);
	freeing_norminette(validated_input, token);
	return (cmd_tree);
}

/* [Original code]
t_cmd	*parse_user_input(char *user_input, t_envp *env)
{
	t_cmd	*cmd_tree;
	char	**validated_input;
	int		*token;
	int		i[2];
	int		tmp;

	if (user_input == NULL || user_input[0] == 0)
		return (NULL);
	cmd_tree = NULL;
	validated_input = validate_input(user_input, env->envp);
	replace_exit_status(&validated_input, 0, 0, 0);
	if (!validated_input)
		return (NULL);
	token = token_data(validated_input);
	if (!token)
		return (NULL);
	i[0] = 0;
	i[1] = token_length(token);
	tmp = syntax_pipe(validated_input, token, i, &cmd_tree);
	if (tmp == -1)
		free_tree(cmd_tree);
	if (tmp == -1)
		return (NULL);
	freeing_norminette(validated_input, token);
	return (cmd_tree);
}
*/
