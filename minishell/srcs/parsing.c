/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/12 20:52:48 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    skip_quotes(char *line, int i)
{
	char c;

	if (line[i] != '\'' && line[i] != '"')
		return (i);
	c = line[i];
	i++;
	while (line[i] && line[i] != c)
		i++;
	return (i + 1);
}

char **split_processes(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		i = skip_quotes(line, i);
		if (line[i] == '|')
			line[i] = '\n';
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
	while (i >= 0 && pid == 0)
	{
		pid = fork();
		// gerer erreur
		i--;
	}
	if (i >= 0)
		printf("process n%d with command %s\n", i, commands[i]);
	wait(NULL);
	return (0);
}

int parse_line(char *line)
{
	char **commands;

	commands = split_processes(line);
	launch_processes(commands);
	free(commands);
	return (0);
}