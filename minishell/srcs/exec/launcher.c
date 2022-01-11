/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 02:09:25 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/08 13:22:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		free_command(command[i]);
		i++;
	}
	free(command);
}

void	free_command(t_command *command)
{
	free(command->io.infile);
	free(command->io.outfile);
	if (command->argv)
		ft_abort(command->argv);
	free(command);
}

void	exec_fork(t_command **commands, int i, int *tube, int fdout)
{
	if (i == 0)
		tube[0] = 0;
	else
		close(tube[1]);
	exec_command(commands, i, tube[0], fdout);
}

void	handle_process(int i, t_command **commands, int *tube, int fdout)
{
	int	pid;

	if (i == 0 && is_builtin(commands[0]->argv[0]))
		commands[0]->exit_status = launch_builtin(commands, 0, fdout);
	else
	{
		pid = fork();
		if (pid == -1)
			ft_exit(errno, "Error", "fork", commands);
		if (pid == 0)
			exec_fork(commands, i, tube, fdout);
		commands[i]->pid = pid;
	}
	if (commands[i + 1])
		close(fdout);
	if (i > 0)
		close(tube[0]);
}

int	launch_processes(t_command **commands)
{
	int	i;
	int	tube[2];
	int	fdout;

	i = 0;
	while (commands[i])
		i++;
	fdout = STDOUT_FILENO;
	while (i > 0)
	{
		i--;
		if (i > 0)
			if (pipe(tube))
				ft_exit(errno, "Error", "pipe", commands);
		handle_process(i, commands, tube, fdout);
		fdout = tube[1];
	}
	return (wait_process(commands));
}
