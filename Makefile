# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 20:23:30 by wlahyani          #+#    #+#              #
#    Updated: 2023/01/26 22:06:32 by wlahyani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c src/lexer.c src/token.c src/parser.c  src/parser_utils.c src/exe.c src/builtins.c src/execution_utils.c

OBJ = ${SRC:%.c=%.o}

FLAGS =  -Wall -Wextra -Werror  -fsanitize=address

READLINE = -lreadline

%.o:%.c
	gcc $(FLAGS)  -c $< -o $@

all : libft $(NAME) 

libft:
	make -C lib_ft

$(NAME): $(OBJ)
	gcc $(FLAGS)  $(OBJ) lib_ft/libft.a $(READLINE)  -o $(NAME)

clean :
	rm -rf $(OBJ) 
	make clean -C lib_ft

fclean : clean
	rm -rf  $(NAME) 
	make fclean -C lib_ft

re : fclean all
