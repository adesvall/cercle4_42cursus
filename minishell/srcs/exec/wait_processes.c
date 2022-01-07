/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:32:57 by user42            #+#    #+#             */
/*   Updated: 2022/01/07 23:24:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sigquit(t_command **cmd, int nb_cmd)
{
	// int	i;

	if (cmd[nb_cmd - 1]->exit_status == 131)
		write(1, "Quit (core dumped)\n", 19);
	// else
	// {
	// 	i = 0;
	// 	while (i < nb_cmd - 1)
	// 	{
	// 		if (cmd[i]->exit_status == 131)
	// 		{
	// 			write(1, "^\\", 2);
	// 			break ;
	// 		}
	// 		i++;
	// 	}
	// }
}

int	wait_process(t_command **cmd)
{
	int		status = 0;
	size_t	i;

	i = 0;
	while (cmd[i])
	{	
		printf("pid: %d\n", cmd[i]->pid); // a suppr
		if (waitpid(cmd[i]->pid, &status, 0) == -1) // ca renvoie -1 qd on fqit sigquit.. pk ?
			printf("ERROR\n");
		printf("STATUS = %d, exit=%d, termsig=%d\n", status, WEXITSTATUS(status), WTERMSIG(status));
		
		if (WIFEXITED(status))
			cmd[i]->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmd[i]->exit_status = WTERMSIG(status) + 128;

		i++;
	}
	
	print_sigquit(cmd, i);
	printf("END: STATUS = %d\n", cmd[i - 1]->exit_status);
	return (cmd[i - 1]->exit_status);
}

int	wait_process2(t_command **cmd)
{
	int		status;
	pid_t	pid_exec;
	size_t	i;

	pid_exec = wait(&status);
	while (pid_exec != -1)
	{
		i = 0;
		while (cmd[i] && cmd[i]->pid != pid_exec)
			i++;
		// if (cmd[i] == NULL)
		// {
		// 	pid_exec = wait(&status);
		// 	continue;
		// }
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
	printf("END: STATUS = %d\n", cmd[i - 1]->exit_status);
	return (cmd[i - 1]->exit_status);
}
