/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/18 21:55:46 by adesvall         ###   ########.fr       */
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

int launch_processes(char **commands)
{
	int i;
	int pid;

	i = 0;
	while (commands[i])
		i++;
	pid = 0;
	while (i > 0 && pid == 0)
	{
		pid = fork();
		// gerer erreur et creer les pipes
		if (pid == 0)
			i--;
	}
	if (commands[i])
	{
		printf("process n°%d with command \"%s\"\n", i, commands[i]);
		parse_process(commands[i]);
		wait(NULL);
		exit(0);
	}
	wait(NULL);
	return (0);
}

int parse_line(char *line)
{
	char **commands;

	commands = split_processes(line);
	launch_processes(commands);
	ft_abort(commands);
	return (0);
}