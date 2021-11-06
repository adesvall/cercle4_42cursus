/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:16:39 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/06 18:09:40 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include  <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define PROMPT "mini\033[34mshell\033[00m : "

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

typedef struct s_var
{
	char *name;
	char *value;
	struct s_var *next;
}				t_var;

typedef struct s_data
{
	int	exit_status;
	int	is_running;
}				t_data;

int		parse_line(char *line, char **env, int exit_status);
int 	parse_process(char *command, int fdin, int fdout, char **env);
int		exec_command(t_command *exe, char **env);
int 	is_builtin(char *cmd);
int		exec_builtin(t_command *exe, t_var **env);
int		heredoc(char *delim);
int		ft_exit(int code, char *str, char *str2, t_command *exe);
void	print_error(char *str, char *str2);

char	*ft_lstjoin(t_list *lst);
int		skip_quotes(char *line, int i);
int		skip_redir(char *line, int i);
int 	skip_notredir(char *line, int i);
char 	*ft_extend(char *str, int extand_vars, int extand_quotes);

#endif
