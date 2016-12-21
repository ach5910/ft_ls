# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahunt <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/30 15:41:53 by ahunt             #+#    #+#              #
#    Updated: 2016/12/06 11:57:08 by ahunt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc 

INC += include libft/include

LIBFT = ./libft/libft.a

LIBFT_LINK = -L libft -lft

CFLAGS += $(foreach d, $(INC), -I$d)

AR = ar

RLIB = ranlib

RM = rm -rf

SRC_BASE = 	main.c \

SRC = $(addprefix src/, $(SRC_BASE))

OBJ = $(addprefix obj/, $(SRC_BASE:.c=.o))

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(OBJ): | obj

obj:
	mkdir -p $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) -o $@ $^  $(CFLAGS) -L libft -lft

debug: $(OBJ)
	$(CC) -fsanitize=address  -o $@ $^  $(CFLAGS) -L libft -lft

clean:
	$(RM) $(OBJ)
	make -C ./libft clean

ls_clean:
	$(RM) $(OBJ)

fclean: ls_clean
	$(RM) $(NAME)
	$(RM) obj
	make -C ./libft fclean

ls_fclean: ls_clean
	$(RM) $(NAME)
	$(RM) obj

re: ls_fclean all
	make -C ./libft re

.PHONY: all clean fclean re
