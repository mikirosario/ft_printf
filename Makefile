# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/14 16:05:23 by mrosario          #+#    #+#              #
#    Updated: 2019/12/19 20:23:16 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c preppers.c parsers.c printers.c intprinters.c

OBJ = $(SRC:.c=.o)

CFLAG = -Wall -Werror -Wextra -I

all: $(NAME)

$(NAME): libftprintf.h
	make -C ./libft
	cp libft/libft.h ./
	cp libft/libft.a ./$(NAME)
	make fclean -C ./libft
	gcc $(CFLAG) ./ -c $(SRC)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) libft.h libft.a

re: fclean all

.PHONY: all clean fclean re
