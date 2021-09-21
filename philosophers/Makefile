NAME		= philosophers

SRCS		= srcs/main.c srcs/init.c srcs/utils.c srcs/philo_life.c srcs/display.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror -I.

all:		${NAME}

$(NAME):	${OBJS}
			gcc ${CFLAGS} -o ${NAME} ${OBJS} -lpthread

.c.o:
			gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re