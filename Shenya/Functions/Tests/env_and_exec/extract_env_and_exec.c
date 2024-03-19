#include <stdio.h>
#include "../../libft/libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>

typedef struct s_envp
{
	t_list	*envlist;
	char	**envarr;
	char	*cd_hist;
	int		count;
}	t_envp;

void rl_replace_line(const char *text, int clear_undo);

int store_envp(t_envp *vars, char **envp)
{
	int 	i;
	char *temp;

	i = 0;
	temp = NULL;
	while (envp[i] != NULL)
	{
		temp = ft_strdup(envp[i]);
		if (!temp)
		{
			//free_list(vars->envlist);
			return (-1);
		}
		ft_lstadd_back(&vars->envlist, ft_lstnew(temp));
		temp = NULL;
		i ++;
	}
	return (0);
}

void free_string(void	*input)
{
	char *str;

	str = (char *)input;
	free (str);
	str = NULL;
}

void clear_envlist(t_envp *my_data)
{
	ft_lstclear(&my_data->envlist, free_string);
}

int extract_envarr(t_envp *my_data)
{
	t_list	*current;
	int i = 0;

	int len = 0;

    current = NULL;
	current = (my_data->envlist);
	len = ft_lstsize(current);
    printf("len: %d\n", len);
	my_data->envarr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!my_data->envarr)
		return (-1);
	my_data->envarr[len] = NULL;
	while (current != NULL)
	{
		my_data->envarr[i] = ft_strdup((char *)current->content);
		if (!my_data->envarr[i])
		{
			//free_arr(vars->envp, i);
			return (-1);
		}
		current = current->next;
		i ++;
	}
    printf("%d : %s\n", i, my_data->envarr[i-1]);
	my_data->count = i;
	return (0);
}

void    clear_envarr(t_envp *my_data)
{
    int i = 0;

    while (my_data->envarr[i] != NULL)
    {
        free(my_data->envarr[i]);
        my_data->envarr[i] = NULL;
        i ++;
    }
    free(my_data->envarr);
    my_data->envarr = NULL;
}

int main (int argc, char **argv, char **envp)
{
    t_envp	my_data;

	my_data.envarr = NULL;
	my_data.cd_hist = NULL;
	my_data.envlist = NULL;
	if (store_envp(&my_data, envp) < 0)
		return (1);
    extract_envarr(&my_data);
    clear_envarr(&my_data);
    clear_envlist(&my_data);
    (void)argc;
    (void)argv;
    return (0);
}