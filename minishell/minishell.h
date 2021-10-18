/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:16:39 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/18 16:54:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define PROMPT "minishell : "


int		parse_line(char *line);
int 	parse_process(char *command);

char	*ft_lstjoin(t_list *lst);
int		skip_quotes(char *line, int i);
int		skip_redir(char *line, int i);

#endif
