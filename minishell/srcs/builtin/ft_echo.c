#include "builtins.h"

int	ft_is_option_n(char *arg)
{
	if (ft_strlen(arg) < 2)
		return (0);
	if (*(arg++) != '-')
		return (0);
	while (*arg)
	{
		if (*(arg++) != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	need_new_line;

	need_new_line = 1;
	if (args && *args)
	{
		while (ft_is_option_n(*args))
		{
			need_new_line = 0;
			args++;
		}
		while (*args)
		{
			ft_putstr_fd(*args, STDOUT_FILENO);
			if (*(++args))
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (need_new_line == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

