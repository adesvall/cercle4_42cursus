/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:33:35 by user42            #+#    #+#             */
/*   Updated: 2022/01/08 11:32:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_env(char **args, t_var *env)
{
	if (!args[1])
	{
		print(env);
		return (0);
	}
	printf("%s\n", "Error: too much arguments.");
	return (1);
}
