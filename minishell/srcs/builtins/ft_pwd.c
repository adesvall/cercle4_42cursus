/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:31:00 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/07 22:31:07 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(char **args, t_var *env)
{
	char	*pwd;

	(void)args;
	(void)env;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
