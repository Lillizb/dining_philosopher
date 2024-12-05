# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 10:53:36 by ygao              #+#    #+#              #
#    Updated: 2024/12/05 15:33:29 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	cc

CFLAGS	=	 -Wall -Wextra -Werror -g

SRC		=	 main.c dining.c parse_input.c threads.c other_actions.c \
			 clean.c dining_utils.c data_init.c init_utils.c time_utils.c \

OBJ		= 	$(SRC:.c=.o)

all:		$(NAME) clean

$(NAME)	: $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:
			fclean all

.PHONY:
			all clean fclean re



