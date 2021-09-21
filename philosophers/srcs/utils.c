/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:32:47 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/21 20:59:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static	int	ft_isin(char c, const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		if (str[i++] == c)
			return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	sign;

	i = 0;
	res = 0;
	sign = -1;
	while (ft_isin(str[i], " \t\n\v\f\r"))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	while (ft_isin(str[i], "0123456789"))
	{
		res *= 10;
		res -= str[i] - '0';
		i++;
	}
	return (res * sign);
}
