/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:11 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/18 23:03:43 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* ft_extend est une fonction qui enleve les guillemets de type '
* et remplace le nom des variables d'environnement par leurs valeurs
*/
char *ft_extend(char *str)
{
	t_list	*lst;
	int		i;
	int 	start;
	char 	*var_name;
	char	*var_value;

	lst = NULL;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		start = i;
		while (str[i] && !ft_isin(str[i], "'$\""))
			i++;
		ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&str[start], i - start)));
		start = i;
		if (str[i] == '\'')
		{
			i = skip_quotes(str, i);
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&str[start + 1], i - 2 - start)));
		}
		else if (str[i] == '$') // il faut ajouter le "
		{
			i++;
			while (str[i] && !ft_isin(str[i], " '$"))
				i++;
			var_name = ft_strndup(&str[start + 1], i - 1 - start);
			var_value = getenv(var_name);
			if (!var_value)
				var_value = "";
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(var_value)));
			free(var_name);
		}
	}
	free(str);
	return (ft_lstjoin(lst));
}

t_redir	parse_redir(char **command)
{
	int i;
	int start;
	t_redir res = (t_redir){0, 0, 0, 0};
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
			res.infile = ft_extend(ft_strndup(&comm[start + 1 + res.heredoc], i - 1 - res.heredoc - start));
		}
		else if (comm[i] == '>')
		{
			if (comm[i + 1] == '>')
				res.outcat = 1;
			else
				res.outcat = 0;
			free(res.outfile);
			i = skip_redir(comm, i);
			res.outfile = ft_extend(ft_strndup(&comm[start + 1 + res.outcat], i - 1 - res.outcat - start));
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
	
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_extend(tab[i]);
		i++;
	}
	return (tab);
}

int disp_tab(char *argv[])
{
	int i=0;
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
	return 0;
}

int parse_process(char *command)
{
	char **argv;
	t_redir io;

	io = parse_redir(&command);

	printf("Command : %s\n", command);
	printf("Infile : %s\n", io.infile);
	printf("Outfile : %s\n", io.outfile);
	
	argv = construct_argv(command);
	disp_tab(argv);

	// exec_command(io, argv);

	ft_abort(argv);
	free(io.infile);
	free(io.outfile);
	free(command);
	return (0);
}
