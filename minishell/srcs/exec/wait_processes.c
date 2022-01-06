/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:32:57 by user42            #+#    #+#             */
/*   Updated: 2022/01/06 12:33:00 by user42           ###   ########.fr       */
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

	// i = 0;
	// while (cmd[i])
	// {
	// 	printf("%s: %d\n", cmd[i]->argv[0], cmd[i]->pid);
	// 	i++;
	// }
	pid_exec = wait(&status);
	while (pid_exec != -1)
	{
		// printf("%d\n", pid_exec);
		i = 0;
		while (cmd[i] && cmd[i]->pid != pid_exec)
			i++;
		// printf("%d\n", cmd[i]->pid);
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
