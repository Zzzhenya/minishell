NAME = minishell

LIBFT		= libft.a
LIBFT_DIR	= libft
LIBFT_PATH	= $(LIBFT_DIR)/$(LIBFT)

CCFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -L/usr/local/opt/readline/lib -L/usr/lib/x86_64-linux-gnu -lreadline

CC = cc

SRCS = src/parsing/change_exit_status.c\
 src/parsing/lexical_analysis.c\
 src/parsing/lexical_chopping.c\
 src/parsing/lexical_expanding.c\
 src/parsing/lexical_quote.c\
 src/parsing/lexical_validating.c\
 src/parsing/syntax_analysis.c\
 src/parsing/syntax_create_node.c\
 src/parsing/syntax_find_target.c\
 src/util/util_error.c\
 src/util/util_free.c\
 src/util/util_skip.c\
 src/util/util_str.c\
 src/util/util_debug.c\
 src/get_cmds.c\
 src/main.c\
 src/envp_actions.c\
 src/signals/signal.c\
 src/executing/executing.c\
 src/executing/temp.c\
 src/builtins/cd.c\
 src/builtins/echo.c\
 src/builtins/env.c\
 src/builtins/exit.c\
 src/builtins/export.c\
 src/builtins/pwd.c\
 src/builtins/unset.c\
 src/executing/setup_redirections.c\
 src/executing/child_process.c\
 src/executing/route_builtins.c\
 src/executing/redirection_syntax_error.c\

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
