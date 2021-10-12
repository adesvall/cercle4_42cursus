/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:09:45 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/15 14:53:33 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	len;

	if (!s1)
		return (0);
	start = 0;
	while (ft_isin(s1[start], set))
		start++;
	len = 0;
	while (s1[start + len])
		len++;
	while (len > 0 && ft_isin(s1[start + len - 1], set))
		len--;
	return (ft_substr(s1, start, len));
}
