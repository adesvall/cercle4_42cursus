/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:11 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/08 23:32:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			if (comm[i + 1] == '<')
			{
				res.heredoc = 1;
				i++;
			}
			else
				res.heredoc = 0;
			free(res.infile);
			i = skip_redir(comm, i);
			res.infile = ft_extend(ft_strndup(&comm[start + 1 + res.heredoc], \
										i - 1 - res.heredoc - start), !res.heredoc, 1, 0);
			if (is_empty(res.infile))
				res.error = -1;
		}
		else if (comm[i] == '>')
		{
			if (comm[i + 1] == '>')
			{
				res.outcat = 1;
				i++;
			}
			else
				res.outcat = 0;
			free(res.outfile);
			i = skip_redir(comm, i);
			res.outfile = ft_extend(ft_strndup(&comm[start + 1 + res.outcat], \
											i - 1 - res.outcat - start), 1, 1, 0);
			if (is_empty(res.outfile))
				res.error = -2;
		}
		else
		{
			if (ft_isin(comm[i], "\"'"))
				i = skip_quotes(comm, i);
			i = skip_notredir(comm, i);
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&comm[start], i - start)));
		}
	}
	free(comm);
	*command = ft_lstjoin(lst);
	return (res);
}

char	**construct_argv(char *line)
{
	int		i;
	char	**tab;

	line = ft_extend(line, 1, 0, 0);
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
		tab[i] = ft_extend(tab[i], 1, 1, 0);
		i++;
	}
	return (tab);
}

int	disp_tab(char *argv[])
{
	int	i;

	i = 0;
	printf("  ARGV :\n");
	while (argv[i])
	{
		printf("    %s\n", argv[i]);
		i++;
	}
	return (0);
}

void parse_error_msg(char c)
{
	printf("minishell: syntax error near unexpected token `%c'\n", c);
}

void free_elems(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
		free(commands[i++]);
}

t_command	**parse_processes(char **commands)
{
	t_command	**exe;
	int			i;

	i = 0;
	while (commands[i])
	{
		if (is_empty(commands[i]))
		{
			free_elems(commands);
			parse_error_msg('|');
			return (NULL);
		}
		i++;
	}
	exe = malloc(sizeof(t_command *) * (i + 1));
	i = 0;
	while (commands[i])
	{
		// printf("PROCESS n°%d with command \"%s\"\n", i, commands[i]);

		exe[i] = malloc(sizeof(t_command));
		exe[i]->io = parse_redir(&(commands[i]));
		exe[i]->argv = NULL;
		if (exe[i]->io.error == -1)
			parse_error_msg('<');
		else if (exe[i]->io.error == -2)
			parse_error_msg('>');
		if (exe[i]->io.error)
		{
			free_elems(commands);
			exe[i + 1] = NULL;
			free_commands(exe);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (commands[i])
	{
		// printf("  Command : %s\n", commands[i]);
		// printf("  Infile  : %s\n", exe[i]->io.infile);
		// printf("  Outfile : %s\n", exe[i]->io.outfile);
		
		exe[i]->argv = construct_argv(commands[i]);
		// disp_tab(exe[i]->argv);
		exe[i]->env = NULL;
		i++;
	}
	exe[i] = NULL;
	return (exe);
}
