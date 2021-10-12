/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:16:24 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/15 15:04:18 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
