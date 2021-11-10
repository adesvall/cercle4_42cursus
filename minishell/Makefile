NAME		= minishell

PARSING		= $(addprefix parsing/, extend.c \
									parse_main.c \
									parse_process.c \
									parse_utils.c)

EXEC		= $(addprefix exec/, launcher.c \
								exec_builtin.c \
								exec_command.c \
								exec_heredoc.c)

BUILTIN		= $(addprefix builtins/, env1.c \
									env2.c \
									ft_cd.c \
									ft_pwd.c \
									ft_export.c \
									ft_unset.c \
									ft_echo.c \
									ft_env.c \
									)

PURESRCS	= main.c error.c $(PARSING) $(EXEC) $(BUILTIN)

SRCS		= $(addprefix srcs/, $(PURESRCS))

OBJS		= $(addprefix objs/, $(PURESRCS:.c=.o))

CFLAGS		= -Wall -Wextra -Werror -I.

all:		${NAME}

$(NAME):	${OBJS} libft/libft.a
			echo $(OBJS)
			clang ${CFLAGS} -lreadline -o ${NAME} ${OBJS} libft/libft.a

objs/%.o:	srcs/%.c objs
			clang $(CFLAGS) -o $@ -c $<

objs:
			@mkdir objs
			@mkdir objs/exec
			@mkdir objs/builtins
			@mkdir objs/parsing

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
