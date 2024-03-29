/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/08 13:51:25 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count(const char *str, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == c)
			n++;
		i++;
	}
	return (n + 1);
}

static char	**simple_split(const char *s, char c)
{
	char	**res;
	int		i;
	int		count;
	int		ncount;

	ncount = ft_count(s, c);
	res = malloc(sizeof(char *) * (ncount + 1));
	if (!s || !res)
		return (0);
	i = 0;
	count = 0;
	while (count < ncount)
	{
		res[count] = ft_strdup_chr(&(s[i]), c);
		if (res[count++] == 0)
			return (ft_abort(res));
		while (s[i] && s[i] != c)
			i++;
		if (s[i])
			i++;
	}
	res[count] = NULL;
	return (res);
}

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
	return (simple_split(line, '\n'));
}

t_command	**parse_line(char *line)
{
	char		**commands;
	t_command	**processes;

	commands = split_processes(line);
	processes = parse_processes(commands);
	free(commands);
	return (processes);
}
