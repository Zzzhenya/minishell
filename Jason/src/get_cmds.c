#include "../include/minishell.h"

/*	[F]
	[Progress]
	1. cmd_tree = NULL;		// Initiailzing cmd_tree struct
	2. validate_input		// Copy all values from "user_input" to "t_data struct".
							   And dividing inputs to token.
	3. replace_exit_status	// Handling ($?: exit status)
	4. token_malloc			// Handling (token): convert value to "token macro".
	5. check_token_length	// Check how many token it is.
	6. syntax_pipe			// Make parse tree
	7. free_tree			// Error handling for [f] syntax_pipe
	8. freeing_norminette	// 
	9. 

	[Difference between "validated_input" vs "token"]
		validated_input:
			T1		T2		T3		T4		T5
			ls		-la		|		cat		-e

		token: 
			T1		T2		T3		T4		T5
			W		W		P		W		W
*/
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
	validated_input = validate_input(user_input, env->envp);
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
