NAME		= minishell

SRCS		= srcs/main.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror -I.

all:		${NAME}

$(NAME):	${OBJS}
			clang ${CFLAGS} -o ${NAME} ${OBJS}

.c.o:
			clang ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re