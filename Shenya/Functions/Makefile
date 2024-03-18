NAME = minishell

SRC = 	read_line.c ft_splitbyspace.c main.c exec_builtin.c \
		builtins/pwd.c builtins/cd.c builtins/env.c builtins/echo.c \
		builtins/export.c builtins/unset.c builtins/exit.c \
		envp_actions.c signal.c

CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS=-L/usr/local/opt/readline/lib

INCLUDE= libft/libft.h minishell.h

LIBFT_DIR= libft

LIBFT=libft.a

CC = cc

OBJ := $(SRC:.c=.o)

all : $(NAME)

%.o: %.c Makefile $(INCLUDE)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "...Compiling $(notdir $<)."

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -lreadline -o $(NAME)
	@echo "...Linking minishell OBJs."

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/$(LIBFT) .
	@echo "...libft.a copied."

clean:
	@rm -rf $(OBJ)
	@echo "...Removing minishell OBJs."
	@make clean -C $(LIBFT_DIR)
	@echo "...Removing libft OBJs."

fclean: clean
	@rm -rf $(NAME)
	@echo "...Removing minishell binary."
	@rm -rf $(LIBFT)
	@echo "...Removing libft.a."

re: fclean all

leak_check:
	make re
	export MallocStackLogging=1
	export MallocStackLoggingNoCompact=1
	leaks --atExit -- ./$(NAME)

.PHONY : all clean fclean leak_check re