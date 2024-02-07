NAME = read_line

SRC = read_line.c ft_splitbyspace.c

LDFLAGS= -L/usr/local/opt/readline/lib

CPPFLAGS= -I/usr/local/opt/readline/include

CC = cc

OBJ := $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) Makefile
	$(CC) $(OBJ) $(CPPFLAGS) $(LDFLAGS) -lreadline -o $@

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