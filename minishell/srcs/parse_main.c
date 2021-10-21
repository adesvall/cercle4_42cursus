/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/21 22:49:37 by adesvall         ###   ########.fr       */
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

int launch_processes(char **commands, char **env)
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
		printf("PROCESS n°%d with command \"%s\"\n", i, commands[i]);
		parse_process(commands[i], tube[0], fdout, env);
		wait(NULL);
		exit(0);
	}
	wait(NULL);
	return (0);
}

int parse_line(char *line, char **env)
{
	char **commands;

	commands = split_processes(line);
	launch_processes(commands, env);
	ft_abort(commands);
	return (0);
}