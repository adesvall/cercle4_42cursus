/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 01:44:08 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/18 17:48:21 by adesvall         ###   ########.fr       */
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
/*
* peut se reveler tres tres tres inutile
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
}*/

char *ft_lstjoin(t_list *lst)
{
	t_list *act;
	int size;
	char *res;

	size = 0;
	act = lst;
	while (act)
	{
		size += ft_strlen(act->content);
		act = act->next;
	}
	res = malloc((size + 1) * sizeof(char));
	*res = 0;
	act = lst;
	while (act)
	{
		ft_strlcat(res, act->content, size + 1);
		act = act->next;
	}
	res[size] = 0;
	ft_lstclear(&lst, free);
	return (res);
}