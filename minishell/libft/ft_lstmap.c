/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:17:51 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/15 15:06:34 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_fill_lst(t_list *lst, t_list *res,
									void *(*f)(void *), void (*del)(void *))
{
	t_list	*cur;
	void	*newcontent;

	cur = res;
	lst = lst->next;
	while (lst)
	{
		newcontent = (*f)(lst->content);
		cur->next = ft_lstnew(newcontent);
		if (cur->next == 0)
		{
			free(newcontent);
			ft_lstclear(&res, del);
			return (0);
		}
		lst = lst->next;
		cur = cur->next;
	}
	return (res);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	void	*newcontent;

	if (!lst)
		return (0);
	newcontent = (*f)(lst->content);
	res = ft_lstnew(newcontent);
	if (res == 0)
	{
		free(newcontent);
		return (0);
	}
	return (ft_fill_lst(lst, res, f, del));
}
