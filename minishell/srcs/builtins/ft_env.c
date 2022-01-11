/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:33:35 by user42            #+#    #+#             */
/*   Updated: 2022/01/08 17:38:46 by user42           ###   ########.fr       */
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
		return (print(env));
	ft_putstr_fd("env: ‘", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd("’: No such file or directory\n", STDERR_FILENO);
	return (1);
}
