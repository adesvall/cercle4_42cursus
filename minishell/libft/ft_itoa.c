/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:26:12 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/15 15:10:54 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		ncpy;
	int		i;

	str = malloc(12 * sizeof(char));
	if (str == 0)
		return (0);
	if (n == -2147483648)
		return (ft_memcpy(str, "-2147483648", 12));
	ncpy = n;
	if (n < 0)
		ncpy = -n;
	str[11] = 0;
	i = 10;
	while (ncpy > 9)
	{
		str[i--] = '0' + ncpy % 10;
		ncpy = ncpy / 10;
	}
	str[i] = '0' + ncpy % 10;
	if (n < 0)
		str[--i] = '-';
	return (ft_memmove(str, str + i, 12 - i));
}
