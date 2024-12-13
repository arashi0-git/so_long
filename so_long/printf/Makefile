# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 20:51:12 by aryamamo          #+#    #+#              #
#    Updated: 2024/12/13 10:24:03 by aryamamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c\
	ft_printf_utils.c\
	ft_print_ptr.c\
	ft_print_unsigned.c\
	ft_treat_hexa.c\

NAME = libftprintf.a
LIBFTNAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFTDIR = ../libft

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFTDIR)/$(LIBFTNAME):
	make -C $(LIBFTDIR)

$(NAME): $(LIBFTDIR)/$(LIBFTNAME) $(OBJS)
	cp $(LIBFTDIR)/$(LIBFTNAME) .
	mv $(LIBFTNAME) $(NAME)
	ar -r $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	make -C $(LIBFTDIR) clean
	
	
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean
	
re: fclean all
