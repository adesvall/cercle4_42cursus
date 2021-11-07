#include <stdio.h>
#include <stdlib.h>
#include "builtins.h"

void	clear_list(t_var **list)
{
	t_var	*var;
	t_var	*tmp;

	if (!list || !(*list))
		return ;
	var = *list;
	while (var)
	{
		tmp = var;
		var = var->next;
		destroy_var(tmp);
	}
	*list = NULL;
}

void	add_var(t_var **env, char *name, char *value)
{
	t_var	**tmp;

	tmp = env;
	while (*tmp)
	{
		if (!ft_strcmp((*tmp)->name, name))
		{
			free((*tmp)->value);
			(*tmp)->value = ft_strdup(value);
			return ;
		}
		tmp = &(*tmp)->next;
	}
	*tmp = malloc_var(name, value);
}

t_var	*load_env(char **args)
{
	int i;
	t_var *globals;
	t_var *elem;

	i = 0;
	while (args[i])
		i++;
	globals = NULL;
	while(i--)
	{
		*ft_strchr(args[i], '=') = 0;
		elem = malloc_var(args[i], ft_strchr(args[i], '\0') + 1);
		*ft_strchr(args[i], '\0') = '=';
		if (!elem)
		{
			clear_list(&globals);
			break ;
		}
		elem->next = globals;
		globals = elem;
	}
	return (globals);
}

char **unload_env(t_var *env)
{
	char **res;
	char *tmp;
	int i;

	res = malloc((env_size(env) + 1) * sizeof(char*));
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		res[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		i++;
		env = env->next;
	}
	return (res);
}

int	env_size(t_var *env)
{
	int size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

// int main(int ac, char **av, char **envp)
// {
// 	t_var *env;

// 	(void)ac;
// 	(void)av;
// 	env = load_env(envp);
// 	while (env->next)
// 	{
// 		printf("%s=%s\n", env->name, env->value);
// 		env = env->next;
// 	}
// 	clear_list(&env);
// 	return (0);
// }
