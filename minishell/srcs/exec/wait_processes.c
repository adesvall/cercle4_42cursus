/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:32:57 by user42            #+#    #+#             */
/*   Updated: 2022/01/08 13:27:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_process(t_command **cmd)
{
	int		status;
	size_t	i;

	status = 0;
	i = 0;
	while (cmd[i])
	{	
		if (waitpid(cmd[i]->pid, &status, 0) == -1)
			printf("ERROR\n");
		if (WIFEXITED(status))
			cmd[i]->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmd[i]->exit_status = WTERMSIG(status) + 128;
		i++;
	}
	if (cmd[i - 1]->exit_status == 131)
		write(1, "^\\Quit (core dumped)\n", 21);
	return (cmd[i - 1]->exit_status);
}
