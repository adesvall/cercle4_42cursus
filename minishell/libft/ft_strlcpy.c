/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:03:59 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/15 14:51:33 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (i < dstsize)
	{
		if (src[i] == 0)
		{
			dst[i] = 0;
			i = dstsize;
		}
		else if (i != dstsize - 1)
			dst[i] = src[i];
		else
			dst[i] = 0;
		i++;
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}
