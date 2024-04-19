/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:51:33 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/25 15:56:15 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	[F]
	Check the type of redirection and return 
	corresponding int for the redirection.

	[Header file]
	# define REDIREC_R 1	// '>'
	# define REDIREC_RR 2	// '>>'
	# define REDIREC_L 3	// '<'
	# define REDIREC_LL 4	// '<<'

	[Progress]
	1. compare "node->cmdstr[0]" with the macros in headfile.
	2. return the corresponding value with macro.
*/
int	redirect_type(t_cmd *node)
{
	if (ft_strcmp(node->cmdstr[0], "<") == 0)
		return (REDIREC_L);
	else if (ft_strcmp(node->cmdstr[0], "<<") == 0)
		return (REDIREC_LL);
	else if (ft_strcmp(node->cmdstr[0], ">") == 0)
		return (REDIREC_R);
	else if (ft_strcmp(node->cmdstr[0], ">>") == 0)
		return (REDIREC_RR);
	return (0);
}

/*	[F]
	[Role]
	New redirection information is created and added to the list,
	and if information is already in the list,
	new information is added to the end of the existing list.
	
	[Korean]
	새로운 리다이렉션 정보를 생성하여 리스트에 추가,
	이미 리스트에 정보가 있는 경우 기존 리스트의 끝에 새로운 정보 추가

	1. 새로운 t_redirec 구조체에 대한 메모리 할당. (= redirection)
	2. 새로운 리다이렉션 구조체에 필요한 데이터 할당.
		r_child: cmdstr[0]
		l-child: redirect_type.
	3. 만약 stdios 리스트가 비어 있다면(NULL) -> 첫 번째 리다이렉션 정보로 설정
	4. 리스트에 이미 리다이렉션 정보가 있다면,
		현재 리스트 끝까지 이동 후 새리다이렉션 정보 추가.

	[Struct]
			N_SIMPLE_REDIREC
			/				\
		(LEFT)				(RIGHT)
	N_REDIREC_TYPE			N_FILE_NAME

	[Reference]
	typedef struct s_redirec
	{
		int				redirec_type;
		char			*filename;
		struct s_redirec	*next_redirec;
	}	t_redirec;

	typedef struct s_cmd
	{
		struct s_cmd		*l_child;
		struct s_cmd		*r_child;
		char				**cmdstr;
		int					node_type;
		int					flag_pipe_exist;
		int					pre_flag;
	}	t_cmd;

	[Progress]
	1. Allocate memory (t_redirec) for redirection.
	2. Put all data about new redirection
		to the new struct(= "redirection"), made in 1st step.
	3. Check whether current redirect is first or not.
		(리다이렉션 정보가 첫 번째인지 여부를 확인)
		3-1. if first
			cpy redirection to *stdios.
		3-2. else
			curr is *stdios.
			track the end of *stdios.
			When meet with end of redirec -> add 
			redirection to the end of *stdios.
*/

static void	trav_redirec(t_redirec	*redirection,
		t_redirec	*curr, t_redirec **stdios)
{
	curr = *stdios;
	while (curr->next_redirec)
		curr = curr->next_redirec;
	curr->next_redirec = redirection;
}

void	redir_error_msg(char *str)
{
	g_exit_status = 2;
	ft_putstr_fd(str, 2);
}

void	execute_simple_redirect(t_cmd *node, t_redirec **stdios)
{
	t_redirec	*redirection;
	t_redirec	*curr;

	if (node->r_child->cmdstr[0] == NULL)
	{
		redir_error_msg("bash: syntax error near unexpected token `newline'\n");
		return ;
	}
	redirection = (t_redirec *)malloc(sizeof(t_redirec));
	if (redirection == NULL)
	{
		redir_error_msg("Error: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	redirection->filename = node->r_child->cmdstr[0];
	redirection->redirec_type = redirect_type(node->l_child);
	redirection->next_redirec = NULL;
	if (*stdios == NULL)
		*stdios = redirection;
	else
		trav_redirec(redirection, curr, stdios);
}
