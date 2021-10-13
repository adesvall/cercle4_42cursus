/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:55:31 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/13 12:51:45 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (res == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && i < n)
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (res == 0)
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
