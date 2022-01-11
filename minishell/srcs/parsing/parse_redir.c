/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:00:08 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/11 16:22:20 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redir_in(char *comm, int start, int i, t_redir *res)
{
	if (comm[i + 1] == '<')
	{
		res->heredoc = 1;
		i++;
	}
	else
		res->heredoc = 0;
	free(res->infile);
	i = skip_redir(comm, i);
	res->infile = ft_extend(ft_strndup(&comm[start + 1 + res->heredoc], \
					i - 1 - res->heredoc - start), !res->heredoc, 1, 0);
	if (is_empty(res->infile))
		res->error = -1;
	return (i);
}

static int	handle_redir_out(char *comm, int start, int i, t_redir *res)
{
	if (comm[i + 1] == '>')
	{
		res->outcat = 1;
		i++;
	}
	else
		res->outcat = 0;
	free(res->outfile);
	i = skip_redir(comm, i);
	res->outfile = ft_extend(ft_strndup(&comm[start + 1 + res->outcat], \
								i - 1 - res->outcat - start), 1, 1, 0);
	if (is_empty(res->outfile))
		res->error = -2;
	return (i);
}

static int	handle_not_redir(char *comm, int start, int i, t_list **lst)
{
	if (ft_isin(comm[i], "\"'"))
		i = skip_quotes(comm, i);
	i = skip_notredir(comm, i);
	ft_lstadd_back(lst, ft_lstnew(ft_strndup(&comm[start], i - start)));
	return (i);
}

t_redir	parse_redir(char **command)
{
	int		i;
	int		start;
	t_redir	res;
	t_list	*lst;
	char	*comm;

	res = (t_redir){0, 0, STDIN_FILENO, 0, STDOUT_FILENO};
	comm = *command;
	i = 0;
	lst = NULL;
	while (comm[i])
	{
		start = i;
		if (comm[i] == '<')
			i = handle_redir_in(comm, start, i, &res);
		else if (comm[i] == '>')
			i = handle_redir_out(comm, start, i, &res);
		else
			i = handle_not_redir(comm, start, i, &lst);
	}
	free(comm);
	*command = ft_lstjoin(lst);
	return (res);
}
