/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:11 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/18 18:11:55 by adesvall         ###   ########.fr       */
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

char **split_command(char *line) // il faut changer ça, "cat>out"
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
* ft_extend est une fonction qui enleve les guillemets de type '
* et remplace le nom des variables d'environnement par leurs valeurs
*/
char *ft_extend(char *str)
{
	t_list *lst;
	int start;
	int	i;
	char 	*var_name;
	char	*var_value;

	i = 0;
	lst = NULL;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		start = i;
		while (str[i] && !ft_isin(str[i], "'$")) // il faut ajouter le "
			i++;
		ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&str[start], i - start)));
		start = i;
		if (str[i] == '\'')
		{
			i = skip_quotes(str, i);
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&str[start + 1], i - 2 - start)));
		}
		else if (str[i] == '$')
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
	return (ft_lstjoin(lst));
}

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
			res.infile = ft_extend(&elem[i][1 + res.heredoc]);
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
			res.outfile = ft_extend(&elem[i][1 + res.outcat]);
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
	printf("Infile : %s\n", io.infile);
	printf("Outfile : %s\n", io.outfile);
	//elem = construct_argv(elem);
	
	return (0);
}
