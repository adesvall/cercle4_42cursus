/*
SOURCES
https://www.digitalocean.com/community/tutorials/how-to-read-and-set-environmental-and-shell-variables-on-linux-fr

https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c

*/

#include "builtins.h"

int	print(t_var *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

int		ft_env(char **args, t_var *env)
{
	if (!args[1])
	{
		print(env);
		return (0);
	}
	printf("%s\n", "Error: too much arguments.");
	return (1);
}



/*

Pour memoire, ce qu'ils faisaient eux :

#include "minishell.h"

int	mini_env(char **args, t_var *var_list)
{
	t_var	*var;

	if (var_list)
	{
		(void)args;
		var = var_list;
		while (var)
		{
			ft_putstr_fd(var->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(var->value, STDOUT_FILENO);
			var = var->next;
		}
	}
	return (0);
}


*/
