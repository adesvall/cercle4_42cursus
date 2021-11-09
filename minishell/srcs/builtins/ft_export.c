#include "builtins.h"

void	sort_tab(t_var	**tab)
{
	int		i;
	int		j;
	t_var	*tmp;
	int		imin;

	i=0;
	while (tab[i])
	{
		imin = i;
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[imin]->name, tab[j]->name) > 0)
				imin = j;
			j++;
		}
		tmp = tab[imin];
		tab[imin] = tab[i];
		tab[i] = tmp;
		i++;
	}
}

t_var	**get_tab(t_var *env)
{
	t_var	**tab;
	int	i;
	
	i = 0;
	tab = malloc((env_size(env)+1) * sizeof(char*));
	while (env)
	{
		tab[i] = env;
		i++;
		env = env->next;
	}
	tab[i] = NULL;
	sort_tab(tab);
	return (tab);
}

int export_sort(t_var *env)
{
	t_var	**tab;
	int i;

	tab = get_tab(env);
	i = 0;
	while (tab[i])
	{
		printf("declare -x %s=%s\n", tab[i]->name, tab[i]->value);
		i++;
	}
	free(tab);
    return (0);
}

int ft_export(char **argv, t_var **env)
{
	int		i;
	char	*egal;

	i = 1;
	if (!argv[1])
		return  (export_sort(*env));
	while (argv[i])
	{
		egal = ft_strchr(argv[i], '=');
		if (!egal)
		{
			i++;
			continue ;
		}
		*egal = 0;
		if (!check_var_name(egal + 1))
			return (1);
		add_var(env, argv[i], egal + 1);
		*egal = '=';
		i++;
	}
    return (0);
}