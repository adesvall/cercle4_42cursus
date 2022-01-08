/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:16:39 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/08 14:48:51 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # define _XOPEN_SOURCE 700
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "srcs/builtins/builtins.h"

# define PROMPT "\033[33mmini\033[34mshell\033[00m : "

typedef struct s_redir
{
	int 	error;
	char	*infile;
	int		heredoc;
	char	*outfile;
	int		outcat;
}			t_redir;

typedef struct s_command
{
	int		pid;
	t_redir	io;
	char	**argv;
	char	**env;
	int		exit_status;
}				t_command;

typedef struct s_data
{
	int		exit_status;
	int		is_running;
	t_var	*env;
}				t_data;

extern t_data	g;

char		*readline_tty(char *line);
t_command	**parse_line(char *line);
t_command	**parse_processes(char **command);
int			launch_processes(t_command **commands);
void		prepare_redir(t_redir io, int *fdin, int *fdout, t_command **commands);
int			exec_command(t_command **exe, int i, int fdin, int fdout);
void		free_command(t_command *command);
void		free_commands(t_command **commands);
int			is_builtin(char *cmd);
int			is_fork_builtin(char *cmd);
int			launch_builtin(t_command **command, int fdin, int fdout);
int			heredoc(char *delim);
int			ft_exit(int code, char *str, char *str2, t_command **exe);
void		print_error(char *str, char *str2);

char		*ft_lstjoin(t_list *lst);
int			is_empty(char *str);
int			skip_quotes(char *line, int i);
int			skip_redir(char *line, int i);
int			skip_notredir(char *line, int i);
char		*ft_extend(char *str, int extand_vars, int extand_quotes, int heredoc);

int			disp_tab(char *argv[]);

int			wait_process(t_command **cmd);

#endif
