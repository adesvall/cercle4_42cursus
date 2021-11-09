/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/09 19:38:08 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data g = {.exit_status = 0, .is_running = 0, .env = NULL};

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
	g.env = load_env(env);
	line = readline(PROMPT);
	while (line)
	{
		// printf("%s\n", line);
		if (*line) // verifier si la ligne ne contient que des whitespaces
			add_history(line);
		g.is_running = 1;
		g.exit_status = parse_line(line, g.exit_status);
		g.is_running = 0;
		free(line);
		line = readline(PROMPT);
	}
	write(1, "exit\n", 5);
}
