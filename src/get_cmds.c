/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:13:44 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 10:13:47 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	free_for_norminette(char **validated_input, int *token)
{
	free_2d(validated_input);
	free(token);
}
/*	[M]
	사용자 입력을 파싱하여 조건에 맞는지 확인하고, 그 결과에 따라 명령어 트리를 생성하는 기능을 구현
	Implements a function that parses user input to check,
	if it meets the conditions and creates a command tree based on the results.

	[Progress]
	1. NULL check for 'user_input'
		Check if user_input is NULL or empty.
	2. validate_input
		count_quote (Check pair & how many)
		count_word (How many)
		check_quote's order
		ft_chopper // seperate one by one as token.
		expansion // $? make it others.
	3. replace_exit_status
		Replace the string 'exit' with a specific value.
	4. token_malloc
		allocate memory for each tokens.
	5. syntax_parsing
		Parses the pipe based on it and constructs a command tree.
	6. Free memory and return for no more useful things.
*/
t_cmd	*parse_user_input(char *user_input, t_envp *env)
{
	t_cmd	*cmd_tree;
	//char	**temp_arr;
	char	**validated_input;
	int		*token;
	int		token_sequence[2];
	int		tmp;

	if (user_input == NULL || user_input[0] == 0)
		return (NULL);
	cmd_tree = NULL;
	//temp_arr = validate_input(user_input, env->envarr);
	validated_input = validate_input(user_input, env->envarr);
	//if (!temp_arr)
	//	return (NULL);
	/* memo */
	// while (*temp_arr != NULL)
	// {
	// 	printf("\n\ttemp_arr: %s", *temp_arr);
	// 	temp_arr++;
	// }
	// printf("\n");
	/* memo */
	//validated_input = strip_empty_strings(temp_arr);
	//free_2d(temp_arr);
	if (!validated_input)
	{
		g_exit_status = EX_CMD_NOT_FOUND;
		return (NULL);
	}
	replace_exit_status(&validated_input, 0, 0, 0);
	token = token_malloc(validated_input);
	if (!token)
		return (NULL);
	token_sequence[0] = 0;
	token_sequence[1] = check_token_length(token);
	tmp = syntax_pipe(validated_input, token, token_sequence, &cmd_tree);
	free_for_norminette(validated_input, token);
	if (tmp == -1)
		free_tree(cmd_tree);
	if (tmp == -1)
		return (NULL);
	return (cmd_tree);
}
/*
[ Original codes, changed cause it's over 25 lines ]

// validated_input = validate_input(user_input, env->envp);
t_cmd	*parse_user_input(char *user_input, t_envp *env)
{
	t_cmd	*cmd_tree;
	char	**validated_input;
	int		*token;
	int		token_sequence[2];
	int		tmp;

	if (user_input == NULL || user_input[0] == 0)
		return (NULL);
	cmd_tree = NULL;
	validated_input = validate_input(user_input, env->envarr);
	if (!validated_input)
		return (NULL);
	replace_exit_status(&validated_input, 0, 0, 0);
	token = token_malloc(validated_input);
	if (!token)
		return (NULL);
	token_sequence[0] = 0;
	token_sequence[1] = check_token_length(token);
	tmp = syntax_pipe(validated_input, token, token_sequence, &cmd_tree);
	if (tmp == -1)
		free_tree(cmd_tree);
	if (tmp == -1)
		return (NULL);
	free_2d(validated_input);
	free(token);
	return (cmd_tree);
}
*/
