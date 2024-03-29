/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:32:26 by user42            #+#    #+#             */
/*   Updated: 2022/01/08 12:35:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	out;

	i = 1;
	out = 0;
	while (args[i])
	{
		if (check_var_name(args[i]) == 1)
			unset_one(args[i], envp);
		else
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			out = 1;
		}
		i++;
	}
	return (out);
}
