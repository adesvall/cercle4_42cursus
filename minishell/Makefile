NAME		= minishell

SRCS		= srcs/main.c srcs/parsing.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror -I.

all:		${NAME}

$(NAME):	${OBJS} libft/libft.a
			clang ${CFLAGS} -lreadline -o ${NAME} ${OBJS} libft/libft.a

.c.o:
			clang ${CFLAGS} -c $< -o ${<:.c=.o}

libft/libft.a:
			make -C libft

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re