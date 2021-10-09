/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/09 16:42:33 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\nsigint\n", 8);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(1, "\nsigquit\n", 9);
	}
}

int	sig_init(void)
{
	struct sigaction sig;

	sig.sa_handler = &handle_sig;
	if (sigaction(SIGINT, &sig, NULL))
		return (1);
	// if (sigaction(SIGQUIT, &sig, NULL))
	// 	return (1);
	return (0);
}

int main()
{
	extern char **environ;
	char *line;

	if (sig_init())
		return (0);
	line = readline(PROMPT);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		line = readline(PROMPT);
	}
	write(1, "exit\n", 5);
}

 