# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/16 11:16:50 by rmenegau          #+#    #+#              #
#    Updated: 2016/10/23 10:29:34 by rmenegau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c \
	  error.c \
	  split_cmd.c \
	  swap_var_quote.c \
	  mini_exit.c \
	  mini_cd.c \
	  mini_echo.c \
	  mini_env.c \
	  mini_setenv.c \
	  mini_unsetenv.c
OBJ = $(SRC:.c=.o)
LIBFT = ../libft
FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -o $@ -c $< -I $(LIBFT)/includes $(FLAGS)

$(NAME): $(OBJ)
	make -C $(LIBFT) re
	gcc -o $(NAME) $^ -L$(LIBFT) -lft $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
