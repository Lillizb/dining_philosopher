NAME	=	philo_github

CC		=	cc

CFLAGS	=	 -Wall -Wextra -Werror

SRCS	=	data_init.c dining.c main.c parse_input.c \
			utils.c \

OBJS	=	$(SRCS: .c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:
			fclean all

.PHONY:
			all clean fclean re




