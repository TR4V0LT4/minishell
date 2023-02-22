# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 20:23:30 by wlahyani          #+#    #+#              #
#    Updated: 2023/02/23 00:05:58 by skhaliff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c src/lexer.c src/token.c src/parser.c  src/parser_utils.c src/exe.c src/builtins.c src/execution_utils.c src/ft_cd.c src/ft_exit.c src/ft_echo.c \
src/ft_export.c src/ft_unset.c src/heredoc.c src/quotes.c


OBJ = ${SRC:%.c=%.o}

FLAGS =  -Wall -Wextra -Werror  #-fsanitize=address

READLINE =  -lreadline -L /Users/skhaliff/.brew/Cellar/readline/8.2.1/lib  -I /Users/skhaliff/.brew/Cellar/readline/8.2.1/include 

%.o:%.c
	gcc $(FLAGS)  -c $< -o $@

all : libft $(NAME) 

libft:
	make -C lib_ft

$(NAME): $(OBJ)
	gcc $(FLAGS)  $(OBJ) lib_ft/libft.a -o $(NAME) $(READLINE)  

clean :
	rm -rf $(OBJ) 
	make clean -C lib_ft

fclean : clean
	rm -rf  $(NAME) 
	make fclean -C lib_ft

re : fclean all
