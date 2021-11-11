/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:11 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/11 14:09:05 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	parse_redir(char **command)
{
	int i;
	int start;
	t_redir res = (t_redir){0, STDIN_FILENO, 0, STDOUT_FILENO};
	t_list *lst;
	char *comm;

	comm = *command;
	i = 0;
	lst = NULL;
	while (comm[i])
	{
		if (ft_isin(comm[i], "\"'"))
			i = skip_quotes(comm, i);
		start = i;
		if (comm[i] == '<')
		{
			if (comm[i + 1] == '<')
				res.heredoc = 1;
			else
				res.heredoc = 0;
			free(res.infile);
			i = skip_redir(comm, i);
			res.infile = ft_extend(ft_strndup(&comm[start + 1 + res.heredoc], i - 1 - res.heredoc - start), !res.heredoc, 1);
		}
		else if (comm[i] == '>')
		{
			if (comm[i + 1] == '>')
				res.outcat = 1;
			else
				res.outcat = 0;
			free(res.outfile);
			i = skip_redir(comm, i);
			res.outfile = ft_extend(ft_strndup(&comm[start + 1 + res.outcat], i - 1 - res.outcat - start), 1, 1);
		}
		else
		{
			i = skip_notredir(comm, i);
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&comm[start], i - start)));
		}
	}
	free(comm);
	*command = ft_lstjoin(lst);
	return (res);
}

char **construct_argv(char *line)
{
	int i;
	char **tab;

	line = ft_extend(line, 1, 0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = skip_quotes(line, i);
		else if (line[i] == ' ')
			line[i++] = '\n';
		else
			i++;
	}
	tab = ft_split(line, '\n');
	free(line);
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_extend(tab[i], 1, 1);
		i++;
	}
	return (tab);
}

int disp_tab(char *argv[])
{
	int i=0;
	printf("  ARGV :\n");
	while (argv[i])
	{
		printf("    %s\n", argv[i]);
		i++;
	}
	return 0;
}

t_command	**parse_processes(char **commands)
{
	t_command **exe;
	int i;

	i = 0;
	while (commands[i])
		i++;
	exe = malloc(sizeof(t_command*) * (i + 1));
	i = 0;
	while (commands[i])
	{
		exe[i] = malloc(sizeof(t_command));
		exe[i]->io = parse_redir(&(commands[i]));

		printf("PROCESS n°%d with command \"%s\"\n", i, commands[i]);
		printf("  Command : %s\n", commands[i]);
		// printf("  Infile  : %s, fd is %d\n", exe[i]->io.infile, fdin);
		// printf("  Outfile : %s, fd is %d\n", exe[i]->io.outfile, fdout);
		
		exe[i]->argv = construct_argv(commands[i]);
		disp_tab(exe[i]->argv);

		exe[i]->env = NULL; // A reflechir
		i++;
	}
	exe[i] = NULL;
	return (exe);
}
