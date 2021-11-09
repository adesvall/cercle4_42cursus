/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:10:52 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/09 19:29:02 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd") 
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_command *exe, t_var **env)
{
	char **argv = exe->argv;

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
		return (ft_exit(0, NULL, NULL, exe));
	return (-2);
}
