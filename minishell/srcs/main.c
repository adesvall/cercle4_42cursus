/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/24 17:40:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int exit_status = 0;

void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\nSIGINT\n", 8);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(1, "\nSIGQUIT\n", 9);
	}
}

int	sig_init(void)
{
	struct sigaction act;

	act.sa_handler = &handle_sig;
	if (sigaction(SIGINT, &act, NULL))
		return (1);
	// if (sigaction(SIGQUIT, &sig, NULL))
	// 	return (1);
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
		parse_line(line, env, &exit_status);
		free(line);
		line = readline(PROMPT);
	}
	write(1, "exit\n", 5);
}
