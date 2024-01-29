NAME = read_line

SRC = read_line.c

LDFLAGS= -L/usr/local/opt/readline/lib

CPPFLAGS= -I/usr/local/opt/readline/include

CC = cc

OBJ := $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) Makefile
	$(CC) $(OBJ) $(CPPFLAGS) -lreadline $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY : all clean fclean