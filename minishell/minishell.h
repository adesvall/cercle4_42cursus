/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:16:39 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/20 20:40:40 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include  <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define PROMPT "minishell : "

typedef struct s_redir
{
	char	*infile;
	int		heredoc;
	char	*outfile;
	int		outcat;
}			t_redir;

typedef struct s_command
{
	t_redir io;
	char **argv;
}				t_command;

int		parse_line(char *line, char **env);
int 	parse_process(char *command, int fdin, int fdout, char **env);
int		exec_command(t_command exe, char **env);
int		ft_exit(int code, char *str, char *str2, t_command *exe);

char	*ft_lstjoin(t_list *lst);
int		skip_quotes(char *line, int i);
int		skip_redir(char *line, int i);
int 	skip_notredir(char *line, int i);
char 	*ft_extend(char *str);

#endif
