# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oruban <oruban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 14:14:12 by rkrechun          #+#    #+#              #
#    Updated: 2024/10/31 18:15:01 by oruban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = cub3d

LIBFT_PATH 	= libft/ 				# 1031 roi
LIB 		= $(LIBFT_PATH)libft.a	# 1031 roi
LIBFT_FLAGS	= -L$(LIBFT_PATH) -lft	# 1031 roi

# Compiler and flags
CC = gcc  #-g -fsanitize=address
FLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I$(HEADER_DIR)
FLAGS += -I$(LIBFT_PATH)
# FLAGS += -g -fsanitize=address // roi
RM = rm -rf

# Header files
HEADER_SRCS = game.h
# HEADER_DIR = libc/
HEADER =  $(HEADER_SRCS)

# Source files
MPATH_SRCS = 	cub3d.c			\
				movement.c		\
				render.c		\
				render2.c		\
				movements.c		\
				parse_map.c		\
				file_check.c 	\
				map_checker.c 	\
				map_rewrite.c
# utils.c			\
# utils2.c		\
#  get_next_line.c	\
# ft_split.c 		\
MPATH_DIR 	= sourse/
MPATH =  $(MPATH_SRCS)
OBJ_M = $(MPATH:.c=.o)

# MLX library path
MLX_DIR = mlx

# MLX library linking flags (adjust if needed)
MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Rule to create .o files from .c files
%.o: %.c $(HEADER) Makefile
	@$(CC) $(FLAGS) -c $< -o $@

# Rule to link .o files into the final executable
# $(NAME): $(OBJ_M)
$(NAME): $(OBJ_M) $(LIB)	# 1031 roi
	@$(CC) $(OBJ_M) $(MLX_LIBS) $(LIBFT_FLAGS) -o $(NAME)
# @$(CC) $(OBJ_M) $(MLX_LIBS) -o $(NAME)

$(LIB):								# 1031 roi
	make -C $(LIBFT_PATH) all bonus
	

# Default rule to build the project
all: $(NAME)

# Rule to remove object files
clean:	
	@$(RM) $(OBJ_M)
	@make -C $(LIBFT_PATH) clean
#	make -C $(LIB_PATH) all bonus clean

# Rule to remove object files and executable
fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) $@

# Rule to recompile the project
re: fclean all

.PHONY: all clean fclean re

norm:
	norminette $(MPATH_SRCS) $(HEADER_SRCS)