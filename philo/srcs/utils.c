/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:32:47 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/23 19:32:03 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)time.tv_sec * 1000 + (uint64_t)time.tv_usec / 1000);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isin(char c, const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_with_overflow_check(const char *str, int *n)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (res > 214748364)
			return (0);
		res *= 10;
		if (res > (2147483647 - (str[i] - '0')))
			return (0);
		res += str[i] - '0';
		i++;
	}
	*n = res;
	return (1);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	i;
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		i = -n;
	}
	else
		i = n;
	if (i > 9)
		ft_putnbr_fd((int)(i / 10), fd);
	c = '0' + i % 10;
	write(fd, &c, 1);
}
