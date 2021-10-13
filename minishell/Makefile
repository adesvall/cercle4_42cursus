NAME		= minishell

SRCS		= srcs/main.c srcs/parse_main.c srcs/parse_process.c srcs/parse_utils.c

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
			make -C libft clean

fclean:		clean
			rm -f ${NAME}
			rm -f libft/libft.a

re:			fclean all

.PHONY:		all clean fclean re