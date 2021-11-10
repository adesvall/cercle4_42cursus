/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:16:53 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/10 16:36:25 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*format_error(char *str2)
{
	char	*res;

	res = ft_strjoin(": ", str2);
	str2 = ft_strjoin(res, ": ");
	free(res);
	res = ft_strjoin(str2, strerror(errno));
	free(str2);
	return (res);
}

void	print_error(char *str, char *str2)
{
	char	*msg;

	msg = "";
	if (str || str2)
	{
		if (str)
			msg = str;
		if (str2)
		{
			str = format_error(str2);
			msg = ft_strjoin(msg, str);
			free(str);
		}
		str = ft_strjoin(msg, "\n");
		if (str2)
			free(msg);
		write(2, str, ft_strlen(str));
		free(str);
	}
}

int	ft_exit(int code, char *s, char *s2, t_command **exe)
{
	print_error(s, s2);
	if (exe)
		free_commands(exe);
	clear_env(&g.env);
	exit(code);
}
