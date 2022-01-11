/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 22:04:16 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/11 16:30:52 by adesvall         ###   ########.fr       */
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
	if (!path)
		return (NULL);
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

void	prepare_redir(t_redir io, int *fdin, int *fdout, t_command **commands)
{
	if (io.infile)
	{
		if (!io.heredoc)
			*fdin = open(io.infile, O_RDONLY);
		else
			*fdin = heredoc(io.infile);
		if (*fdin == -1)
			ft_exit(1, io.infile, "can't open file", commands);
	}
	if (io.outfile)
	{
		if (!io.outcat)
			*fdout = open(io.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			*fdout = open(io.outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fdout == -1)
			ft_exit(1, io.outfile, "can't open file", commands);
	}
}

int	exec_command(t_command **commands, int i, int fdin, int fdout)
{
	char		*path;
	t_command	*exe;

	exe = commands[i];
	prepare_redir(exe->io, &fdin, &fdout, commands);
	if (is_empty(exe->argv[0]))
		ft_exit(0, NULL, NULL, commands);
	path = parse_path(get_var(g_data.env, "PATH"), exe->argv[0]);
	if (!path)
		ft_exit(127, exe->argv[0], "command not found", commands);
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
	exe->env = unload_env(g_data.env);
	if (execve(path, exe->argv, exe->env) == -1)
		ft_exit(126, exe->argv[0], "can't execute command", commands);
	return (0);
}
