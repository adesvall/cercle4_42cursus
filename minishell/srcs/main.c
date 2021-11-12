/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/12 14:26:07 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data g = {.exit_status = 0, .is_running = 0, .env = NULL};

void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g.is_running)
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

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isin(line[i], " \t"))
			return (0);
		i++;
	}
	return (1);
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
		if (*line && !is_empty(line))
		{
			add_history(line);
			g.is_running = 1;
			g.exit_status = parse_line(line, g.exit_status);
			g.is_running = 0;
		}
		free(line);
		line = readline(PROMPT);
	}
	write(1, "exit\n", 5);
	clear_env(&g.env);
}
