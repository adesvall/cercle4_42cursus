/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 01:44:08 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/13 14:58:27 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    skip_quotes(char *line, int i)
{
	char c;

	// if (line[i] != '\'' && line[i] != '"')
	// 	return (i);
	c = line[i];
	i++;
	while (line[i + 1] && line[i] != c)
		i++;
	return (i + 1);
}

int skip_redir(char *line, int i)
{
	char c;

	// if (line[i] != '<' && line[i] != '>')
	// 	return (i);
	c = line[i];
	i++;
	if (line[i] == c)
		i++;
	while (line[i] == ' ')
		i++;
	return (i);
}

char *find_var(char **environ, char *var_name)
{
	int i;
	int len;

	len =  ft_strlen(var_name);
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], var_name, len) \
				&& environ[i][len] == '=')
			return (ft_strdup(&environ[i][len]));
		i++;
	}
	return (ft_strdup(""));
}
