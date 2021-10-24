NAME		= minishell

SRCS		= srcs/main.c srcs/parse_main.c srcs/parse_process.c srcs/parse_utils.c \
				srcs/exec_command.c srcs/extend.c srcs/error.c srcs/heredoc.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror -I. -fsanitize=address

all:		${NAME}

$(NAME):	${OBJS} libft/libft.a
			clang ${CFLAGS} -lreadline -o ${NAME} ${OBJS} libft/libft.a

.c.o:
			clang ${CFLAGS} -c $< -o ${<:.c=.o}

libft/libft.a:
			make -C libft bonus

clean:
			rm -f ${OBJS}
			make -C libft clean

fclean:		clean
			rm -f ${NAME}
			rm -f libft/libft.a

re:			fclean all

.PHONY:		all clean fclean re
