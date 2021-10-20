/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 22:04:16 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/20 20:56:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	exec_command(t_command exe, char **env)
{
	int fdin;
	char *path;
	int fdout;
	t_redir io = exe.io;
	char **argv = exe.argv;

	fdin = io.heredoc;
	fdout= io.outcat;
	if (io.infile)
	{
		if (!io.heredoc)
			fdin = open(io.infile, O_RDONLY);
		if (fdout == -1)
			ft_exit(errno, io.outfile, "can't open file", &exe);
	}
	if (io.outfile)
	{
		if (!io.outcat)
			fdout = open(io.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fdout = open(io.outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fdout == -1)
			ft_exit(errno, io.outfile, "can't open file", &exe);
	}

	path = parse_path(getenv("PATH"), argv[0]);
	if (!path)
	 	ft_exit(0, argv[0], "command not found", &exe);
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
	if (execve(path, argv, env) == -1)
		ft_exit(errno, "can't execute command", argv[0], &exe);
	return (1);
}