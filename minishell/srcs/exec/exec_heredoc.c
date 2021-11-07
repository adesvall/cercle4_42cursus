/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:42:04 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/07 19:41:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int heredoc(char *delim)
{
	int hd_pipe[2];
	char *line;

	if (pipe(hd_pipe) == -1)
		ft_exit(errno, "Error", "pipe", NULL);
	line = readline("> ");
	while (line && ft_strcmp(delim, line))
	{
		line = ft_extend(line, 1, 0);
		write(hd_pipe[1], line, ft_strlen(line));
		write(hd_pipe[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(hd_pipe[1]);
	return (hd_pipe[0]);
}