/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:10:13 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/22 01:14:46 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display(t_glob *glob, int id, char *str)
{
	pthread_mutex_lock(&glob->write);
	ft_putnbr_fd(get_time() - glob->start, 1);
	write(1, "\t", 1);
	if (id != -1)
		ft_putnbr_fd(id + 1, 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&glob->write);
}
