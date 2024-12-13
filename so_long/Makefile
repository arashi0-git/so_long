# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 12:15:38 by aryamamo          #+#    #+#              #
#    Updated: 2024/12/13 19:29:40 by aryamamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror


SRCS = main.c\
	make_map.c\
	map_validation.c\
	map_validation2.c\
	handle_P.c\
	image.c\
	$(GNL)/get_next_line.c\
	$(GNL)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

GNL = ./gnl
LIBFT = ./libft/libft.a
PRINTF = ./printf/libftprintf.a
MLX = ./minilibx-linux
LIBS = -lXext -lX11 -lm -lz
NAME = so_long


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(MLX)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(MLX)/libmlx.a $(LIBS) -o $(NAME)

$(LIBFT):
	make -C ./libft

$(PRINTF):
	make -C ./printf

$(MLX)/libmlx.a:
	make -C $(MLX)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)
	make -C ./libft clean
	make -C ./printf clean
	make -C $(MLX) clean


fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean
	make -C ./printf fclean
	make -C $(MLX) fclean

re: fclean all

