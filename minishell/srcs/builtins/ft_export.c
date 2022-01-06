

#include "builtins.h"

int	check_var_value(char *name)
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

void	sort_tab(t_var	**tab)
{
	int		i;
	int		j;
	t_var	*tmp;
	int		imin;

	i = 0;
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
	int		i;
	
	i = 0;
	tab = malloc((env_size(env) + 1) * sizeof(char*));
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

int	export_sort(t_var *env)
{
	t_var	**tab;
	int		i;

	tab = get_tab(env);
	i = 0;
	while (tab[i+1])
	{
		printf("declare -x %s=%s\n", tab[i]->name, tab[i]->value);
		i++;
	}
	free(tab);
	return (0);
}

int	ft_export(char **argv, t_var **env)
{
	int		i;
	char	*egal;

	i = 1;
	if (!argv[1])
		return (export_sort(*env));
	while (argv[i])
	{
		egal = ft_strchr(argv[i], '=');
		if (!egal)
		{
			i++;
			continue ;
		}
		*egal = 0; // Message d'erreur de export $TOTO=12 incomplet quand TOTO=11 par exemple
		printf("Egal + 1 : %s\n", (egal + 1));
		printf("Len : %zu\n",ft_strlen(egal + 1));
		printf("Argv[i + 1] : %s\n", argv[i + 1]);
		printf("Argv[i] : %s\n", argv[i]);	
		printf("Len argv[i]: %zu\n",ft_strlen(argv[i]));
		if (ft_strlen(argv[i]) == 0)
		{
			printf("export: `=%s': not a valid identifier\n", egal + 1);
			return (1);			
		}
		if (*(egal + 1) == 0 && argv[i + 1] != 0)
		{
			printf("export: `%s': not a valid identifier\n", argv[i + 1]);
			return (1);
		}
		if (!check_var_name(argv[i]))
		{
			printf("export: `%s': not a valid identifier\n", argv[i]);
			return (1);
		}
		add_var(env, argv[i], egal + 1);
		*egal = '=';
		i++;
	}
	return (0);
}
