/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 02:09:25 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/12 13:47:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command **command)
{
	int i;

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
	ft_abort(command->argv);
	free(command);
}

int launch_processes(t_command **commands, int exit_status)
{
	int i;
	int pid;
	int	tube[2];
	int fdout;

	i = 0;
	while (commands[i])
		i++;
	if (i == 1 && is_builtin(commands[0]->argv[0]))
		return (launch_builtin(commands));
	pid = 0;
	fdout = 1;
	while (i > 0 && pid == 0)
	{
		if (commands[i])
			if (pipe(tube))
				ft_exit(errno, "Error", "pipe", commands);
		pid = fork();
		if (pid == -1)
			ft_exit(errno, "Error", "fork", commands);
		if (pid == 0)
		{
			if (commands[i])
			{
				fdout = tube[1];
				close(tube[0]);
			}
			i--;
		}
	}
	if (commands[i])
	{
		if (i == 0)
			tube[0] = 0;
		else
			close(tube[1]);
		exec_command(commands, i, tube[0], fdout);
		wait(NULL);
		printf("olala\n");
		exit(1);
	}
	waitpid(pid, &exit_status, 0);
	printf("exit_status : %d\n", exit_status);
	return (exit_status);
}
