/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/08 14:48:12 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Relink 3eme make
#include "minishell.h"

t_data	g_data = {.exit_status = 0, .is_running = 0, .env = NULL};

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_data.is_running)
			rl_redisplay();
		g_data.exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

int	sig_init(void)
{
	if (signal(SIGINT, handle_sig))
		return (1);
	if (signal(SIGQUIT, handle_sig))
		return (1);
	return (0);
}

int	handle_line(char *line)
{
	t_command	**processes;
	int			status;

	processes = parse_line(line);
	if (!processes)
		return (2);
	status = launch_processes(processes);
	free_commands(processes);
	return (status);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	if (sig_init())
		return (0);
	(void)ac;
	(void)av;
	g_data.env = load_env(env);
	line = readline_tty(PROMPT);
	while (line)
	{
		if (*line && !is_empty(line))
		{
			add_history(line);
			g_data.is_running = 1;
			g_data.exit_status = handle_line(line);
			g_data.is_running = 0;
		}
		free(line);
		line = readline_tty(PROMPT);
	}
	write(1, "exit\n", 5);
	clear_env(&g_data.env);
	return (g_data.exit_status);
}
