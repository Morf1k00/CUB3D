# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 16:32:54 by rkrechun          #+#    #+#              #
#    Updated: 2024/08/27 16:06:38 by rkrechun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

HEADER = libc/cub3D.h

M_PATH = sources
S_PATH = cub3d.c\
		gnl.c\
		parse_map.c

OBJ_M = $( $(M_PATH)/ $(S_PATH):.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ_M)
	$(CC) $(FLAGS) $(OBJ_M) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ_M)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re