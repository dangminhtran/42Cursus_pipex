# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 18:51:55 by dangtran          #+#    #+#              #
#    Updated: 2025/02/14 19:02:33 by dangtran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS= -Wall -Wextra -Werror -I${HEADER_DIR} -g

SRCS_DIR = 	$(addprefix sources/,error.c free.c pipex.c main.c) $(LIBFT)

SRCS_OBJ = ${SRCS_DIR:.c=.o}

LIBFT = $(addprefix libft/, ft_putstr_fd.c)

HEADER_DIR=./includes/

all: $(NAME)

$(NAME): $(SRCS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS_OBJ) $(LIBFT) -o $(NAME)


clean :
	rm -f ${SRCS_OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all