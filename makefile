# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 14:14:12 by rkrechun          #+#    #+#              #
#    Updated: 2024/11/07 16:51:58 by rkrechun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = cub3d

LIBFT_PATH 	= libft/ 				# 1031 roi
LIB 		= $(LIBFT_PATH)libft.a	# 1031 roi
LIBFT_FLAGS	= -L$(LIBFT_PATH) -lft	# 1031 roi

# Compiler and flags
CC = @gcc  #-g -fsanitize=address
FLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I$(HEADER_DIR)
FLAGS += -I$(LIBFT_PATH)
# FLAGS += -g -fsanitize=address // roi
RM = rm -rf
SILENT = @

# Header files
HEADER_SRCS = lib/game.h
# HEADER_DIR = libc/
HEADER =  $(HEADER_SRCS)

# Source files
MPATH_DIR = game/
MPATH_SRCS = 	cub3d.c			\
				movement.c		\
				render.c		\
				render2.c		\
				movements.c		\
				parse_map.c		\
				file_check.c 	\
				map_checker.c 	\
				map_rewrite.c	\
				count_tabs.c	\
				errors_func.c	
# utils.c			\
# utils2.c		\
#  get_next_line.c	\
# ft_split.c 		\
MPATH_DIR 	= sourse/
MPATH =  $(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M = $(MPATH:.c=.o)

# MLX library path
MLX_DIR = mlx

# MLX library linking flags (adjust if needed)
MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Rule to create .o files from .c files
$(MPATH_DIR)%.o: $(MPATH_DIR)%.c $(HEADER) Makefile
		$(SILENT)$(CC) $(FLAGS) -c $< -o $@

# Rule to link .o files into the final executable
# $(NAME): $(OBJ_M)
$(NAME): $(OBJ_M) $(LIB)	# 1031 roi
		$(SILENT)$(CC) $(OBJ_M) $(MLX_LIBS) $(LIBFT_FLAGS) -o $(NAME)
		@echo "$(GREEN)$(BOLD)\n\n\t\t\t$(NAME) created!\n\n$(DEFAULT)"
# @$(CC) $(OBJ_M) $(MLX_LIBS) -o $(NAME)

$(LIB):								# 1031 roi
	@ make -C $(LIBFT_PATH) --silent all bonus
	

# Default rule to build the project
all: $(NAME)

# Rule to remove object files
clean:	
	$(SILENT) $(RM) $(OBJ_M)
	$(SILENT) make -C $(LIBFT_PATH) --silent clean
	@echo "\t\t$(YELLOW)$(BOLD)  Object files deleted!$(DEFAULT)"
#	make -C $(LIB_PATH) all bonus clean

# Rule to remove object files and executable
fclean: clean
	$(SILENT) $(RM) $(NAME)
	$(SILENT) make -C $(LIBFT_PATH) --silent $@
	@echo "\t\t\t$(RED)$(BOLD)All deleted!$(DEFAULT)"

# Rule to recompile the project
re: fclean all

.PHONY: all clean fclean re

norm:
	norminette $(MPATH_SRCS) $(HEADER_SRCS)

RED = \033[31m
GREEN = \033[32m
DEFAULT = \033[0m
BOLD = \033[1m
YELLOW = \033[33m 