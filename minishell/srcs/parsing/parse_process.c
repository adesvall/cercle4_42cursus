/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:11 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/11 16:21:12 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	parse_error_msg(char c)
{
	ft_putstr_fd("minishell: syntax error near `", STDERR_FILENO);
	write(STDERR_FILENO, &c, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	free_elems(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
		free(commands[i++]);
}

int	parse_redirs_loop(char **commands, t_command **exe)
{
	int	i;

	i = 0;
	while (commands[i])
	{
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
			return (0);
		}
		exe[i]->env = NULL;
		i++;
	}
	return (1);
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
	if (!parse_redirs_loop(commands, exe))
		return (NULL);
	i = 0;
	while (commands[i])
	{
		exe[i]->argv = construct_argv(commands[i]);
		i++;
	}
	exe[i] = NULL;
	return (exe);
}
