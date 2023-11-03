# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 15:48:02 by ghwa              #+#    #+#              #
#    Updated: 2023/11/03 10:53:53 by ghwa             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES  = pipex.c initall.c cmd.c fork.c exit.c
SOURCES = $(addprefix codes/, $(CFILES))
OBJECTS = ${SOURCES:.c=.o}
CFLAGS = -Wall -Werror -Wextra -g3 -ggdb -fsanitize=address
NAME = pipex
CC = cc

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) ../libft/libft.a -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all

.PHONY = all clean fclean re