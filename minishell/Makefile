NAME		= minishell

PARSING		= $(addprefix parsing/, extend.c \
									parse_main.c \
									parse_process.c \
									parse_utils.c)

EXEC		= $(addprefix exec/, exec_builtin.c \
								exec_command.c \
								exec_heredoc.c)

BUILTIN		= $(addprefix builtin/, env1.c \
									env2.c \
									ft_cd.c \
									ft_pwd.c \
									ft_export.c \
									ft_unset.c \
									ft_echo.c \
									ft_env.c \
									)

SRCS		= $(addprefix srcs/, main.c error.c $(PARSING) $(EXEC) $(BUILTIN))

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
