# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 12:03:20 by aryamamo          #+#    #+#              #
#    Updated: 2025/01/16 13:05:29 by aryamamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRCS = ./src/check_map_utils.c\
	./src/check_map.c\
	./src/error.c\
	./src/handle_game.c\
	./src/image.c\
	./src/main.c\
	./gnl/get_next_line.c\
	./gnl/get_next_line_utils.c

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
MLXDIR = ./minilibx-linux
MLX = $(MLXDIR)/libmlx.a
CC = cc
CFLAGS = -Wall -Wextra -Werror


OBJS = $(SRCS:%.c=%.o)

FRAMEWORK = -L ./minilibx-linux -lmlx -I ./minilibx-linux -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(FRAMEWORK)

$(LIBFT):
	make -C $(LIBFTDIR)

$(MLX):
	make -C $(MLXDIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTDIR) clean


fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean


re: fclean all