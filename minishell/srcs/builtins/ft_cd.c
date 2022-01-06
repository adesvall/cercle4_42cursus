/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:34:14 by user42            #+#    #+#             */
/*   Updated: 2022/01/06 12:34:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	proceed_cd(char **argv, t_var *env)
{
	char	*from;
	char	*to;

	from = getcwd(NULL, 0);
	if (chdir(argv[1]))
	{
		free(from);
		print_error("minishell: cd", argv[1]);
		return (1);
	}
	to = getcwd(NULL, 0);
	if (from)
		add_var(&env, "OLDPWD", from);
	if (to)
		add_var(&env, "PWD", to);
	free(from);
	free(to);
	return (0);
}

int	ft_cd(char **argv, t_var *env)
{
	char	*home;

	if (!argv[1])
	{
		home = get_var(env, "HOME");
		return (ft_cd((char *[3]){"cd", home, NULL}, env));
	}
	if (argv[1] && argv[2])
	{
		write(2, "minishell: cd : trop d'arguments", 32);
		return (1);
	}
	return (proceed_cd(argv, env));
}
