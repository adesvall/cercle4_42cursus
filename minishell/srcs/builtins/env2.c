/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:40:34 by user42            #+#    #+#             */
/*   Updated: 2022/01/06 12:40:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_var(t_var *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_var	*malloc_var(char *name, char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	var->next = NULL;
	if (!var->name || !var->value)
	{
		destroy_var(var);
		var = NULL;
	}
	return (var);
}

void	destroy_var(t_var *var)
{
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
}
