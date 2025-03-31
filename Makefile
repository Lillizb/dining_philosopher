
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
			$(MAKE) fclean
			$(MAKE) all

.PHONY:
			all clean fclean re



