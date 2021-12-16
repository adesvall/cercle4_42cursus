#include "builtins.h"

int	check_var_name(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(*name) && *name != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset_one(char *str, t_var **env)
{
	int		i;
	t_var	*tmp;

	i = 0;
	while (*env)
	{
		if (ft_strcmp(str, (*env)->name) == 0)
		{
			tmp = (*env)->next;
			destroy_var(*env);
			*env = tmp;
			return (0);
		}
		env = &(*env)->next;
		i++;
	}
	return (0);
}

int	ft_unset(char **args, t_var **envp)
{
	int	i;

	i = 1;
	/// rajouter check caracteres unset Ulysse=7
	while (args[i])
	{
		if (check_var_name(args[i]) == 1)
			unset_one(args[i], envp);
		i++;
	}
	return (0);
}
/*
int main(int ac, char **av, char **envp)
{
	t_var *env;

	(void)ac;
	(void)av;
	env = load_env(envp);
		printf("hkvrw\n");
	add_var(&env, "TEST1", "1");
	printf("%p\n", env);
	add_var(&env, "TEST2", "2");
	
	//ft_export(av, &env);
	ft_unset(av, &env);
	print(env);

	clear_list(&env);
	return (0);
}
*/
