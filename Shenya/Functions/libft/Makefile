# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 11:14:14 by sde-silv          #+#    #+#              #
#    Updated: 2023/06/08 14:43:08 by sde-silv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	libft.a

SRCS 	= 	ft_bzero.c \
			ft_isdigit.c \
			ft_putchar_fd.c \
			ft_strlcat.c \
			ft_substr.c \
			ft_calloc.c \
			ft_isprint.c \
		 	ft_putendl_fd.c \
			ft_strlcpy.c \
			ft_tolower.c \
			ft_isalnum.c \
			ft_memcpy.c \
			ft_putnbr_fd.c \
			ft_strlen.c \
			ft_toupper.c \
			ft_isalpha.c \
			ft_memmove.c \
			ft_putstr_fd.c \
			ft_strncmp.c \
			ft_isascii.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_atoi.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_strdup.c \
			ft_split.c \
			ft_itoa.c \
			print_chr.c \
			print_str.c \
			print_int.c \
			print_ptr.c \
			print_hex.c \
			print_uint.c \
			ft_printf.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_isspace.c \
			ft_atoll.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_errexit.c \
			ft_splitbyspace.c

OBJS	= $(SRCS:.c=.o)

CFLAGS  = -Wall -Werror -Wextra -g

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "...libft.a archived."

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	@rm -rf $(OBJS)
	@echo "...libft OBJs cleaned."

fclean: clean
	@rm -rf $(NAME)
	@echo "...libft.a cleaned."

re: fclean all

.PHONY: all fclean re clean
