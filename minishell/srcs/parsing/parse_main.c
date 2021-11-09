/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/09 20:48:26 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **split_processes(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = skip_quotes(line, i);
		else if (line[i] == '|')
			line[i++] = '\n';
		else
			i++;
	}
	return (ft_split(line, '\n'));
}

int launch_processes(t_command **commands, int exit_status)
{
	int i;
	int pid;
	int	tube[2];
	int fdout;

	i = 0;
	while (commands[i])
		i++;
	pid = 0;
	fdout = 1;
	while (i > 0 && pid == 0)
	{
		if (commands[i])
			if (pipe(tube))
				ft_exit(errno, "Error", "pipe", NULL);
		pid = fork();
		if (pid == -1)
			ft_exit(errno, "Error", "fork", NULL);
		if (pid == 0)
		{
			if (commands[i])
			{
				fdout = tube[1];
				close(tube[0]);
			}
			i--;
		}
	}
	if (commands[i])
	{
		if (i == 0)
			tube[0] = 0;
		else
			close(tube[1]);
		exec_command(commands[i], tube[0], fdout);
		wait(NULL);
		exit(1);
	}
	wait(&exit_status);
	return (exit_status);
}

int parse_line(char *line, int exit_status)
{
	char **commands;
	t_command	**processes;
	int	ret;

	commands = split_processes(line);
	processes = parse_processes(commands);
	ret = launch_processes(processes, exit_status);
	free(commands);
	return (ret);
}