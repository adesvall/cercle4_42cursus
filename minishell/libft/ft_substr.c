/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:23:09 by adesvall          #+#    #+#             */
/*   Updated: 2020/11/22 19:15:26 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, size_t start, size_t len)
{
	size_t	i;
	char	*res;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		start = ft_strlen(s);
	res = malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (0);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
