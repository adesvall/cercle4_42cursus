/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upeyret <upeyret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:31:42 by adesvall          #+#    #+#             */
/*   Updated: 2021/12/19 17:12:28 by upeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sigquit(t_command **cmd, int nb_cmd)
{
	int	i;

	if (cmd[nb_cmd - 1]->exit_status == 131)
		write(1, "^\\Quit\n", 7);
	else
	{
		i = 0;
		while (i < nb_cmd - 1)
		{
			if (cmd[i]->exit_status == 131)
			{
				write(1, "^\\", 2);
				break ;
			}
			i++;
		}
	}
}

int	wait_process(t_command **cmd)
{
	int		status;
	pid_t	pid_exec;
	size_t	i;

	pid_exec = wait(&status);
	while (pid_exec != -1)
	{
		i = 0;
		while (cmd[i]->pid != pid_exec)
			i++;
		if (WIFEXITED(status))
			cmd[i]->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmd[i]->exit_status = WTERMSIG(status) + 128;
		pid_exec = wait(&status);
	}
	i = 0;
	while (cmd[i])
		i++;
	print_sigquit(cmd, i);
	return (cmd[i - 1]->exit_status);
}
