/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:31:42 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/08 12:13:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_export2(char **argv, int i)
{
	int	out;

	out = 0;
	if (ft_strlen(argv[i]) == 0)
	{
		printf("export: `': not a valid identifier\n");
		out = 1;
	}
	return (out);
}

int	ft_export3(char **argv, char *egal, int i, int flag)
{
	if (ft_strlen(argv[i]) == 0)
	{
		printf("export: `=%s': not a valid identifier\n", egal + 1);
		flag = 1;
	}
	if (*(egal + 1) == 0 && argv[i + 1] != 0 && flag == 0)
	{
		printf("export: `%s': not a valid identifier\n", argv[i + 1]);
		flag = 1;
	}
	if (!check_var_name(argv[i]) && flag == 0)
	{
		printf("export: `%s': not a valid identifier\n", argv[i]);
		flag = 1;
	}
	return (flag);
}

int	ft_export(char **argv, t_var **env)
{
	int		i;
	char	*egal;
	int		flag;
	int		out;

	i = 0;
	out = 0;
	if (!argv[1])
		return (export_sort(*env));
	while (argv[++i])
	{
		egal = ft_strchr(argv[i], '=');
		flag = ft_export2(argv, i);
		if (!egal)
			continue ;
		*egal = 0;
		flag = ft_export3(argv, egal, i, flag);
		if (flag == 0)
			add_var(env, argv[i], egal + 1);
		*egal = '=';
		out = out + flag;
	}
	return ((out > 0) * 1);
}
