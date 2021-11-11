/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 22:04:16 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/11 13:59:03 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_access(char **dir, char *cmd)
{
	int		i;
	char	*curr;

	i = 0;
	while (dir[i])
	{
		curr = ft_strjoin(dir[i], cmd);
		if (!access(curr, F_OK))
		{
			free(cmd);
			ft_abort(dir);
			return (curr);
		}
		free(curr);
		i++;
	}
	free(cmd);
	ft_abort(dir);
	return (NULL);
}

char	*parse_path(char *path, char *cmd)
{
	char	**dir;
	char	*tmp;

	if (!access(cmd, F_OK))
		return (ft_strjoin("", cmd));
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (NULL);
	dir = ft_split(path, ':');
	if (!dir)
	{
		free(tmp);
		return (NULL);
	}
	return (find_access(dir, tmp));
}

int	exec_command(t_command **commands, int i, int fdin, int fdout)
{
	char *path;
	t_command *exe;

	exe = commands[i];
	if (exe->io.infile)
	{
		if (!exe->io.heredoc)
			fdin = open(exe->io.infile, O_RDONLY);
		else
			fdin = heredoc(exe->io.infile);
		if (fdin == -1)
			ft_exit(errno, exe->io.infile, "can't open file", commands);
	}
	if (exe->io.outfile)
	{
		if (!exe->io.outcat)
			fdout = open(exe->io.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fdout = open(exe->io.outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fdout == -1)
			ft_exit(errno, exe->io.outfile, "can't open file", commands);
	}
	// if (!is_builtin(exe->argv[0]))
	// {
	path = parse_path(get_var(g.env, "PATH"), exe->argv[0]);
	if (!path)
		ft_exit(errno, exe->argv[0], "command not found", commands);
	// }
	// else
	// 	path = exe->argv[0];
	if (fdin != STDIN_FILENO)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	// add_var(&g.env, "_", path);
	// if (is_builtin(exe->argv[0]))
	// 	exit(exec_builtin(exe, &g.env));
	exe->env = unload_env(g.env);
	if (execve(path, exe->argv, exe->env) == -1)
		ft_exit(errno, exe->argv[0], "can't execute command", commands);
	return (0);
}