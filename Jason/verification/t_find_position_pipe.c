#include <stdio.h>
#include <stdlib.h>

extern int	g_exit_status;

typedef struct s_cmd
{
	struct s_cmd		*left_child;
	struct s_cmd		*right_child;
	char				**cmdstr;
	int					node_type;
	int					pipe_exist;
	int					pre_flag;
}	t_cmd;

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIREC 3
# define T_S_QUOTE 4
# define T_D_QUOTE 5

int	token_length(int *token)
{
	int	i;

	i = 0;
	while (token[i] != 0)
		i ++;
	return (i);
}

int	find_position_pipe(int *token, int target, int *i)
{
	int	count;

	count = i[0];
	while (count < i[1])
	{
		if (token[count] == target)
			return (count);
		count++;
	}
	return (-1);
}

int main(void)
{
    int token[6] = {T_WORD, T_WORD, T_PIPE, T_WORD, T_WORD, T_NULL};
    int i[2] = {0, token_length(token)};
    int pipe_pos = find_position_pipe(token, T_PIPE, i);
    int index = 0;
    printf("\n");
    while (index < 2)
    {
        printf("i[%d]: %d\n", index, i[index]);
        index++;
    }
    printf("\n");
    index = 0;
    while (token[index])
    {
        printf("token[%d]: %d\n", index, token[index]);
        index++;
    }
    printf("\n");
    printf("pipe_pose: %d\n", pipe_pos);
    printf("\n");
    return (0);
}