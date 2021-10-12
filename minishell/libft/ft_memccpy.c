/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:35:36 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 15:03:46 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char *)src)[i] != (unsigned char)c)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	if (i < n && ((unsigned char *)src)[i] == (unsigned char)c)
	{
		((char *)dest)[i] = ((char *)src)[i];
		return (dest + i + 1);
	}
	else
		return (0);
}
