# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 18:51:55 by dangtran          #+#    #+#              #
#    Updated: 2025/02/15 15:42:03 by dangtran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS= -Wall -Wextra -Werror -I${HEADER_DIR} -g

SRCS_DIR = 	$(addprefix sources/, error.c manage.c pipex.c main.c) $(LIBFT)

SRCS_OBJ = ${SRCS_DIR:.c=.o}

LIBFT = $(addprefix libft/, ft_split.c ft_putstr_fd.c ft_strdup.c ft_strlcat.c)

HEADER_DIR=./includes/

all: $(NAME)

$(NAME): $(SRCS_OBJ)
	$(CC) $(CFLAGS) $(SRCS_OBJ) -o $(NAME)


clean :
	rm -f ${SRCS_OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all