/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 01:44:08 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/07 16:28:45 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(char *line, int i)
{
	char	c;

	c = line[i];
	i++;
	while (line[i + 1] && line[i] != c)
		i++;
	return (i + 1);
}

int	skip_redir(char *line, int i)
{
	char	c;

	c = line[i];
	i++;
	if (line[i] == c)
		i++;
	while (line[i] == ' ')
		i++;
	while (line[i] && !ft_isin(line[i], " ><"))
	{
		if (ft_isin(line[i], "'\""))
			i = skip_quotes(line, i) - 1;
		i++;
	}
	return (i);
}

int	skip_notredir(char *line, int i)
{
	while (line[i] && !ft_isin(line[i], "<>"))
	{
		if (ft_isin(line[i], "\"'"))
			i = skip_quotes(line, i) - 1;
		i++;
	}
	return (i);
}

char	*ft_lstjoin(t_list *lst)
{
	t_list	*act;
	int		size;
	char	*res;

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
