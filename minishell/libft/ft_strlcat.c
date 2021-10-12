/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:42:17 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/15 15:09:18 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (dst[j] && j < dstsize)
		j++;
	i = 0;
	while (i + j < dstsize)
	{
		if (src[i] == 0)
		{
			dst[j + i] = 0;
			i = dstsize;
		}
		else if (i + j != dstsize - 1)
			dst[i + j] = src[i];
		else
			dst[i + j] = 0;
		i++;
	}
	return (j + ft_strlen(src));
}
