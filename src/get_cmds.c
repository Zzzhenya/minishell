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

int	if_token_order_weird(int *tokens, int numTokens, char **input)
{
	if (check_token_order(tokens, numTokens) == -1)
	{
		g_exit_status = 2;
		free_for_norminette(input, tokens);
		printf("Syntax error\n");
		return (-1);
	}
	return (0);
}

/*	[F]
	[ Definition ]
	리다이렉션, 파이프의 순서가 맞는지 체크하는 함수

	[ Example ]
	bash: >		-> Syntax error
	bash: | 'a' -> Syntax error
	bash: | | | -> Syntax error
*/
int	check_token_order(const int *tokens, int numTokens)
{
	int	i;
	int	current_token;
	int	next_token;

	i = 0;
	while (i < numTokens)
	{
		current_token = tokens[i];
		if (i < numTokens - 1)
			next_token = tokens[i + 1];
		else
			next_token = -1;
		if (current_token == T_REDIREC || current_token == T_PIPE)
		{
			if ((next_token != -1 && (next_token == T_REDIREC
						|| next_token == T_PIPE))
				|| next_token == -1
				|| (current_token == T_PIPE && i == 0))
				return (-1);
		}
		i++;
	}
	return (0);
}

/*	[F]
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
static void	setup_token_arr(int *token_sequence, int *token)
{
	token_sequence[0] = 0;
	token_sequence[1] = check_token_length(token);
}

t_cmd	*parse_user_input(char *user_input, t_envp *env, t_cmd *cmd_tree)
{
	char	**validated_input;
	int		*token;
	int		token_sequence[2];
	int		tmp;

	if (user_input == NULL || user_input[0] == 0)
		return (NULL);
	validated_input = validate_input(user_input, env->envarr);
	if (!validated_input)
		return (NULL);
	replace_exit_status(&validated_input, 0, 0, 0);
	token = token_malloc(validated_input);
	if (!token)
		return (NULL);
	setup_token_arr(token_sequence, token);
	if (if_token_order_weird(token, token_sequence[1], validated_input) == -1)
		return (NULL);
	if (setup_and_run_heredoc(token, validated_input, env) == 0)
		tmp = syntax_pipe(validated_input, token, token_sequence, &cmd_tree);
	free_for_norminette(validated_input, token);
	if (tmp == -1)
		free_tree(cmd_tree);
	if (tmp == -1)
		return (NULL);
	return (cmd_tree);
}
