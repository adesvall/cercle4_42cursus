/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upeyret <upeyret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 02:09:25 by adesvall          #+#    #+#             */
/*   Updated: 2021/12/12 17:18:59 by upeyret          ###   ########.fr       */
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

int	launch_processes(t_command **commands, int exit_status)
{
	int	i;
	int	pid;
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
		if (i == 0 && is_builtin(commands[0]->argv[0]))
			launch_builtin(commands, 0, fdout);
		else
		{
			pid = fork();
			if (pid == -1)
				ft_exit(errno, "Error", "fork", commands);
			if (pid == 0)
				exec_fork(commands, i, tube, fdout);
		}
		if (commands[i + 1])
			close(fdout); 
		if (i > 0)
			close(tube[0]);
		fdout = tube[1];
	}
	waitpid(pid, &exit_status, 0); // attention gestion du sigquit lorsque cat est en attente + verifier qu'aucun  builtin ne met l'entree standard en attente + comprendre tout lol
	// anything like expr $? + $?
	// printf("exit_status : %d\n", exit_status);//You can repeat the same in bash and compare it.
	return (exit_status);
}
