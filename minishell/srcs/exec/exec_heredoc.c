/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:42:04 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/06 12:32:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline_tty(char *line)
{
	if (isatty(STDIN_FILENO))
		return (readline(line));
	else
		return (readline(NULL));
}

int	heredoc(char *delim)
{
	int		hd_pipe[2];
	char	*line;

	if (pipe(hd_pipe) == -1)
		ft_exit(errno, "Error", "pipe", NULL);
	line = readline_tty("> ");
	while (line && ft_strcmp(delim, line))
	{
		line = ft_extend(line, 1, 0, 1);
		write(hd_pipe[1], line, ft_strlen(line));
		write(hd_pipe[1], "\n", 1);
		free(line);
		line = readline_tty("> ");
	}
	close(hd_pipe[1]);
	return (hd_pipe[0]);
}
