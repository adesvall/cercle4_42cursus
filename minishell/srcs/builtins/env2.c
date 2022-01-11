/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upeyret <upeyret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:40:34 by user42            #+#    #+#             */
/*   Updated: 2022/01/11 17:25:37 by upeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_var(t_var *env, char *name)
{
	if (ft_strlen(name) == 0)
		return ("$");
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
