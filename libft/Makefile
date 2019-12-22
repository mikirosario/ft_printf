# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/09 00:04:22 by mrosario          #+#    #+#              #
#    Updated: 2019/12/22 09:27:38 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	  ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c \
	  ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c \
	  ft_toupper.c ft_calloc.c ft_strdup.c ft_strlcpy.c ft_substr.c \
	  ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_isspace.c ft_putchar.c ft_putstr.c ft_filler.c ft_llitoa.c \
	  ft_llitoa_base.c ft_strtolower.c ft_thousep.c ft_lluitoa.c \
	  ft_lluitoa_base.c ft_wputstr.c ft_wstrlen.c

BSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	   ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	   ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c


OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

CFLAG = -Wall -Werror -Wextra -I

all: $(NAME)

$(NAME): libft.h
	gcc $(CFLAG) ./ -c $(SRC) $(BSRC)
	ar -rc $(NAME) $(OBJ) $(BOBJ)
	ranlib $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: libft.h
	gcc $(CFLAG) ./ -c $(BSRC)
	ar -rc $(NAME) $(BOBJ)
	ranlib $(NAME)

.PHONY: all clean fclean re bonus
