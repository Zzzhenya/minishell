NAME = minishell

NAME1 = fork

NAME2 = path

SRC = 	extract_env_and_exec.c

SRC1 = fork_env.c export.c unset.c

SRC2 = get_path.c

CFLAGS = -Wall -Werror -Wextra -g -v 

LDFLAGS=-L/usr/local/opt/readline/lib

#CPPFLAGS=-I/usr/local/opt/readline/include

INCLUDE= libft/libft.h fork.h

LIBFT_DIR= ../../libft

LIBFT=libft.a

CC = cc

OBJ := $(SRC:.c=.o)

OBJ1 := $(SRC1:.c=.o)


all : $(NAME)

%.o: %.c Makefile $(INCLUDE)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "...Compiling $(notdir $<)."

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -lreadline -o $(NAME)
	@echo "...Linking minishell OBJs."

$(NAME1): $(LIBFT) $(OBJ1) $(NAME2)
	@$(CC) $(CFLAGS) $(OBJ1) $(LIBFT) $(LDFLAGS) -lreadline -o $(NAME1)
	@echo "...Linking minishell OBJs."

$(NAME2):
	$(CC) $(CFLAGS) $(SRC2) -o $(NAME2)

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/$(LIBFT) .
	@echo "...libft.a copied."

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ1)
	@echo "...Removing minishell OBJs."
	@make clean -C $(LIBFT_DIR)
	@echo "...Removing libft OBJs."

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME1)
	@rm -rf $(NAME2)
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