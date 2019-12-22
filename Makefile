# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/14 16:05:23 by mrosario          #+#    #+#              #
#    Updated: 2019/12/22 14:24:03 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c preppers.c parsers.c printers.c intprinters.c hexprinters.c \
	  intformat.c uintformat.c charformat.c checkers.c intprinteraux.c

#BSRC = ft_printf_bonus.c preppers_bonus.c parsers_bonus.c printers_bonus.c intprinters_bonus.c

OBJ = $(SRC:.c=.o)

#BOBJ = $(BSRC:.c=.o)

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

#bonus: libftprintf.h
#	make -C ./libft
#	cp libft/libft.h ./
#	cp libft/libft.a ./$(NAME)
#	make fclean -C ./libft
#	gcc $(CFLAG) ./ -c $(BSRC)
#	ar -rc $(NAME) $(BOBJ)
#	ranlib $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) libft.h libft.a

re: fclean all

.PHONY: all clean fclean re bonus
