NAME = minishell

SRC = read_line.c ft_splitbyspace.c main.c

ifeq ($(detected_OS), Darwin)
	LDFLAGS= -L/usr/local/opt/readline/lib
	CPPFLAGS= -I/usr/local/opt/readline/include
else
	LDFLAGS= -L/usr/local/lib
	CPPFLAGS= -I/usr/local/include
endif

#LDFLAGS= -L/lib/x86_64-linux-gnu/ -lreadline

CFLAGS = -Wall -Werror -Wextra -g -v

#LDFLAGS= -L/usr/local/opt/readline/lib

#CPPFLAGS= -I/usr/local/opt/readline/include

CC = cc

OBJ := $(SRC:.c=.o)

all : $(NAME)

#%.o: %.c Makefile
#	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(CPPFLAGS) $(LDFLAGS) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

leak_check:
	make re
	export MallocStackLogging=1
	export MallocStackLoggingNoCompact=1
	leaks --atExit -- ./$(NAME)

.PHONY : all clean fclean leak_check re