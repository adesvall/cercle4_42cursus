/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 22:14:40 by adesvall          #+#    #+#             */
/*   Updated: 2020/11/21 22:14:44 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;

	cur = *lst;
	while (cur)
	{
		*lst = (*lst)->next;
		ft_lstdelone(cur, del);
		cur = *lst;
	}
	lst = 0;
}
