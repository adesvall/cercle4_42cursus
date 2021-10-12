/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:50:52 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/15 15:08:58 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (*s2 == 0)
		return (s1);
	while (j + ft_strlen(s2) - 1 < ft_strlen(s1) && s1[j + ft_strlen(s2) - 1] \
												&& j + ft_strlen(s2) <= len)
	{
		i = 0;
		while (s2[i] == s1[j + i])
		{
			if (s2[i + 1] == 0)
				return (s1 + j);
			i++;
		}
		j++;
	}
	return (0);
}
