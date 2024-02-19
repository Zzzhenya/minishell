NAME = minishell

SRC = read_line.c ft_splitbyspace.c main.c

#ifeq ($(detected_OS), Darwin)
#	LDFLAGS= -L/usr/local/opt/readline/lib
#	CPPFLAGS= -I/usr/local/opt/readline/include
#endif
#else
#	LDFLAGS= -L/lib/x86_64-linux-gnu/
	#CPPFLAGS= -I/usr/local/include
#endif

#LDFLAGS= -L/lib/x86_64-linux-gnu/ -lreadline

CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS= -L/usr/local/opt/readline/lib

CPPFLAGS= -I/usr/local/opt/readline/include

INCLUDE=libft/libft.h minishell.h

#LDFLAGS= -L/usr/local/lib
#CPPFLAGS= -I/usr/local/include
#$(CPPFLAGS) $(LDFLAGS)

LIBFT_DIR= libft

LIBFT=libft.a

CC = cc

OBJ := $(SRC:.c=.o)

all : $(NAME)

%.o: %.c Makefile $(INCLUDE)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "...Compiling $(notdir $<)."

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
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