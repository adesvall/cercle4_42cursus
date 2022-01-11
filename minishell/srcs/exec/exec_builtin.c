/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:10:52 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/08 17:47:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	builtin_exit(char **argv, t_command **exes)
{
	int	i;

	write(2, "exit\n", 5);
	if (!argv[1])
		return (ft_exit(g_data.exit_status, NULL, NULL, exes));
	if (argv[2])
	{
		write(STDERR_FILENO, "minishell: exit : too many arguments\n", 37);
		return (1);
	}
	i = 0;
	if (argv[1][i] == '+' || argv[1][i] == '-')
		i++;
	while (argv[1][i])
	{
		if (!ft_isin(argv[1][i], "0123456789") || i > 10)
		{
			ft_putstr_fd("minishell: exit : argument numérique nécessaire\n", 2);
			ft_exit(2, NULL, NULL, exes);
		}
		i++;
	}
	g_data.exit_status = ft_atoi(argv[1]);
	return (ft_exit(g_data.exit_status, NULL, NULL, exes));
}

int	exec_builtin(t_command **exes, t_var **env)
{
	char	**argv;

	argv = exes[0]->argv;
	if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argv, *env));
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv));
	if (!ft_strcmp(argv[0], "env"))
		return (ft_env(argv, *env));
	if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argv, env));
	if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd(argv, *env));
	if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(argv, env));
	if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv, exes));
	return (-2);
}

void	recover_old_fd(int oldin, int tempin, int oldout, int tempout)
{
	if (tempin != STDIN_FILENO)
	{
		close(tempin);
		dup2(oldin, STDIN_FILENO);
		close(oldin);
	}
	if (tempout != STDOUT_FILENO)
	{
		close(tempout);
		dup2(oldout, STDOUT_FILENO);
		close(oldout);
	}
}

int	launch_builtin(t_command **commands, int tempin, int tempout)
{
	int			oldout;
	int			oldin;
	int			ret;
	t_command	*exe;

	exe = commands[0];
	prepare_redir(exe->io, &tempin, &tempout, commands);
	if (tempin != STDIN_FILENO)
	{
		oldin = dup(STDIN_FILENO);
		dup2(tempin, STDIN_FILENO);
	}
	if (tempout != STDOUT_FILENO)
	{
		oldout = dup(STDOUT_FILENO);
		dup2(tempout, STDOUT_FILENO);
	}
	ret = exec_builtin(commands, &g_data.env);
	recover_old_fd(oldin, tempin, oldout, tempout);
	return (ret);
}
