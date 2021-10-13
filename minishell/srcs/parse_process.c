/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:11 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/13 16:04:50 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_redir
{
	char	*infile;
	int		heredoc;
	char	*outfile;
	int		outcat;
}			t_redir;

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
* ft_extend est une fonction qui enleve les guillemets d'indication
* et remplace le nom des variables d'environnement par leurs valeurs
*
char *ft_extend(char *str, int i)
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
*/

t_redir	parse_redir(char **elem)
{
	int i;
	t_redir res = (t_redir){0, 0, 0, 0};

	i = 0;
	while (elem[i])
	{
		// printf("%s\n", elem[i]);
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
		else if (elem[i][0] == '>')
		{
			if (elem[i][1] == '>')
				res.outcat = 1;
			else
				res.outcat = 0;
			free(res.outfile);
			//redir.outfile = ft_extend(&elem[i][1 + res.outcat]);
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
	free(elem);
	return (res);
}

int parse_process(char *command)
{
	char **elem;
	t_redir io;

	elem = split_command(command);
	io = parse_redir(elem);
	elem = construct_argv(elem);
	
	return (0);
}
