/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/10 16:42:33 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_processes(char *line)
{
	int	i;

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

int	parse_line(char *line, int exit_status)
{
	char		**commands;
	t_command	**processes;
	int			ret;

	commands = split_processes(line);
	processes = parse_processes(commands);
	free(commands);
	ret = launch_processes(processes, exit_status);
	free_commands(processes);
	return (ret);
}
