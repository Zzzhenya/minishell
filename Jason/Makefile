NAME = minishell

LIBFT		= libft.a
LIBFT_DIR	= libft
LIBFT_PATH	= $(LIBFT_DIR)/$(LIBFT)

CCFLAGS = -Wall -Werror -Wextra
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lreadline

CC = cc -g

SRCS = src/builtins/unset.c\
 src/builtins/env.c\
 src/builtins/cd.c\
 src/builtins/echo.c\
 src/builtins/exit.c\
 src/builtins/export.c\
 src/builtins/pwd.c\
 src/fork/exec_func_tools.c\
 src/fork/recur_tree_execute.c\
 src/fork/simple_cmd.c\
 src/fork/simple_cmd_stdins.c\
 src/fork/simple_cmd_stdouts.c\
 src/fork/simple_cmd_tools.c\
 src/fork/simple_cmd_pid.c\
 src/fork/wait_commands.c\
 src/parsing/ch_complete.c\
 src/parsing/ch_com_expan.c\
 src/parsing/ch_complete2.c\
 src/parsing/ch_complete3.c\
 src/parsing/get_a_command.c\
 src/parsing/lexical_analysis.c\
 src/parsing/syntax_analysis.c\
 src/parsing/tree_node_gen.c\
 src/parsing/argv_modification.c\
 src/parsing/norminette_tools.c\
 src/tools/free_tools.c\
 src/tools/ft_strcmp.c\
 src/tools/get_envpath.c\
 src/tools/array_length.c\
 src/tools/check_token_existence.c\
 src/tools/chopping_str_tool.c\
 src/tools/chopping_word_tools.c\
 src/tools/copy_2d_arr.c\
 src/main.c\
 src/signals/signal.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

clean:
			rm -f $(OBJS)
			make clean -C $(LIBFT_DIR)
fclean: clean
			rm -f $(NAME)
			rm -f $(LIBFT)
re: fclean all

%.o: %.c include/minishell.h
			$(CC) $(CCFLAGS) -c $< -o $@
$(LIBFT):
			make bonus -C $(LIBFT_DIR)
			mv $(LIBFT_DIR)/$(LIBFT) .

$(NAME): $(OBJS) $(LIBFT)
			$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $^ -lreadline
.PHONY: all clean fclean re
