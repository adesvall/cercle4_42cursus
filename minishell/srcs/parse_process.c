/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:11 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/12 20:55:17 by adesvall         ###   ########.fr       */
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
	char	*file;
	int		doub;
}			t_redir;

typedef struct s_proc
{
    char    *command;
    t_redir   in;
    t_redir   out;
    
}               t_proc;

char **split_command(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		i = skip_quotes(line, i);
		if (line[i] == ' ')
			line[i] = '\n';
		i++;
	}
	return (ft_split(line, '\n'));
}

char *ft_strdup_c(const char *str, char c)
{
	int i;
	char *res;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	res = malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] && str[i] != c)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);	
}

char *extract_name(char *command, int i)
{
	char *res:

	res = NULL;
	while (command[i] == ' ')
		i++;
	while (command[i] != ' ' && command[i])
	{
		if (command[i] == '\'' && command[i] == '"') // peut etre pas necessaire ici
			join(res, &command[i + 1]);
	}
}

t_redir	parse_infile(char *command)
{
	int i;
	t_redir res = (t_redir){0, 0};

	i = 0;
	while (command[i])
	{
		i = skip_quotes(command, i);
		if (command[i] == '<')
		{
			if (command[i + 1] == '<')
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
}

int parse_process(char *command)
{
	char *infile;
	char *outfile;

	//il faut en fait direct ici expand les $ et les "'
	// ou peut etre encore apres avoir split avec les espaces
	argv = split_command(command);
}

