/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/06 17:49:27 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile t_data g = {.exit_status = 0, .is_running = 0};

void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\nSIGINT\n", 8);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g.is_running)
			rl_redisplay();
		g.exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

int	sig_init(void)
{
	struct sigaction act;

	act.sa_handler = &handle_sig;
	if (sigaction(SIGINT, &act, NULL))
		return (1);
	if (sigaction(SIGQUIT, &act, NULL))
		return (1);
	return (0);
}

int main(int ac, char **av, char **env)
{
	char *line;

	(void)ac;
	(void)av;
	if (sig_init())
		return (0);
	line = readline(PROMPT);
	while (line)
	{
		// printf("%s\n", line);
		if (line && *line)
			add_history(line);
		g.is_running = 1;
		g.exit_status = parse_line(line, env, g.exit_status);
		g.is_running = 0;
		free(line);
		line = readline(PROMPT);
	}
	write(1, "exit\n", 5);
}
