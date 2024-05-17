NAME = minishell

LIBFT		= libft.a
LIBFT_DIR	= libft
LIBFT_PATH	= $(LIBFT_DIR)/$(LIBFT)

CCFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -L/usr/local/opt/readline/lib -L/usr/lib/x86_64-linux-gnu -lreadline

CC = cc

SRCS = src/parsing/lexical_analysis.c\
 src/parsing/lexical_change_exit_status.c\
 src/parsing/lexical_chopping_tool.c\
 src/parsing/lexical_chopping.c\
 src/parsing/lexical_expanding_tool.c\
 src/parsing/lexical_expanding_tool2.c\
 src/parsing/lexical_expanding_tool3.c\
 src/parsing/lexical_expanding_tool4.c\
 src/parsing/lexical_expanding.c\
 src/parsing/lexical_quote.c\
 src/parsing/lexical_validating_cnt_wd.c\
 src/parsing/lexical_validating_cnt_wd1.c\
 src/parsing/lexical_validating.c\
 src/parsing/setup_and_run_heredoc.c\
 src/parsing/stage_run_heredoc.c\
 src/parsing/syntax_analysis.c\
 src/parsing/syntax_create_node.c\
 src/parsing/syntax_find_target.c\
 src/util/util_debug.c\
 src/util/util_error.c\
 src/util/util_free.c\
 src/util/util_skip.c\
 src/util/util_str.c\
 src/get_cmds.c\
 src/main.c\
 src/signals/heredoc_signal.c\
 src/signals/signal.c\
 src/executing/child_process.c\
 src/executing/cmd_functions.c\
 src/executing/configure_pipes.c\
 src/executing/execute_one_builtin.c\
 src/executing/execute_simple_cmd.c\
 src/executing/execute_simple_redirect.c\
 src/executing/here_doc_functions.c\
 src/executing/redirection_error_handle.c\
 src/executing/route_builtins.c\
 src/executing/search_tree.c\
 src/executing/setup_left_redirections.c\
 src/executing/setup_redirections.c\
 src/executing/setup_right_redirections.c\
 src/executing/wait_blocked_cmds.c\
 src/builtins/builtin_utils.c\
 src/builtins/cd_utils.c\
 src/builtins/cd.c\
 src/builtins/echo.c\
 src/builtins/env.c\
 src/builtins/exit_utils.c\
 src/builtins/exit.c\
 src/builtins/export_utils.c\
 src/builtins/export.c\
 src/builtins/pwd.c\
 src/builtins/unset.c\
 src/environment/create_env_list.c\
 src/environment/extract_env_arr.c\
 src/environment/init_env.c\
 src/environment/reset_env.c\
 src/environment/setup_env.c

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

leaks: 
	make re
	#valgrind -s --show-leak-kinds=all --leak-check=full ./$(NAME)
	valgrind -s --suppressions=./readline.supp --show-leak-kinds=all --leak-check=full --track-fds=yes ./$(NAME)

leak_log:
	make re
	valgrind -s --suppressions=./readline.supp --show-leak-kinds=all --leak-check=full ./$(NAME) 2>&1 | tee log1.txt

.PHONY: all clean fclean re leaks leak_log
