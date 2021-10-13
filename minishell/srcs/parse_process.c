/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:11 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/13 15:30:31 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
typedef union u_dir
{
    int fd;
}               t_dir;
*/

typedef struct s_redir
{
	char	*infile;
	int		heredoc;
	char	*outfile;
	int		outcat;
}			t_redir;

typedef struct s_proc
{
	char	*command;
	t_redir	in;
	t_redir	out;
}               t_proc;

char **split_command(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isin(line[i], "<>"))
		{
			i = skip_redir(line, i);
			continue;
		}	
		if (ft_isin(line[i], "\"'"))
		{
			i = skip_quotes(line, i);
			continue;
		}	
		if (line[i] == ' ')
			line[i] = '\n';
		i++;
	}
	return (ft_split(line, '\n'));
}

/*
char *extract_name(char *command, int i)
{
	int start;

	while (command[i] == ' ')
		i++;
	start = i;
	while (command[i] != ' ' && command[i])
	{
		i = skip_quotes(command, i);
		i++;
	}
	return (ft_strndup(&command[start], i - start));
}

t_redir	parse_iofile(char *command, char io)
{
	int i;
	t_redir res = (t_redir){0, 0};

	i = 0;
	while (command[i])
	{
		i = skip_quotes(command, i);
		if (command[i] == io)
		{
			if (command[i + 1] == io)
			{
				redir.doub = 1;
				i++;
			}
			free(redir.file);
			redir.file = extract_name(command, i + 1);
		}
		i++;
	}
	return (res);
}*/

t_redir	parse_redir(char **elem)
{
	int i;
	t_redir res = (t_redir){0, 0, 0, 0};

	i = 0;
	while (elem[i])
	{
		printf("%s\n", elem[i]);
		if (elem[i][0] == '<')
		{
			if (elem[i][1] == '<')
				res.heredoc = 1;
			else
				res.heredoc = 0;
			free(res.infile);
			//redir.infile = ft_extend(&elem[i][1 + res.heredoc]);
			free(elem[i]);
			elem[i] = (void*)1;
		}
		i++;
	}
	return (res);
}

char **construct_argv(char **elem)
{
	int i;
	int len;
	char **res;

	i = 0;
	len = 0;
	while (elem[i])
	{
		if (elem[i] != (void*)1)
			len++;
		i++;
	}
	res = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (elem[i])
	{
		if (elem[i] != (void*)1)
		{
			// res[i] = ft_extend(elem[i]);
			free(elem[i]);
		}
		i++;
	}
	res[len] = NULL;
	return (res);
}

int parse_process(char *command)
{
	char **elem;
	t_redir io;

	elem = split_command(command);
	io = parse_redir(elem);
	elem = construct_argv(elem);

	// il faut en fait direct ici expand les $ et les "'
	// ou peut etre encore apres avoir split avec les espaces
	return (0);
}

