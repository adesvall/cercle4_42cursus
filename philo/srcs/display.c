/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:10:13 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/23 19:35:37 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display(t_glob *glob, int id, char *str)
{
	uint64_t	time;

	pthread_mutex_lock(&glob->write);
	time = get_time() - glob->start;
	if (sim_is_running(glob))
	{
		ft_putnbr_fd(time, 1);
		write(1, "\t", 1);
		if (id != -1)
			ft_putnbr_fd(id + 1, 1);
		write(1, str, ft_strlen(str));
	}
	pthread_mutex_unlock(&glob->write);
}

void	stop_sim(t_glob *glob)
{
	pthread_mutex_lock(&glob->m_is_running);
	glob->is_running = 0;
	pthread_mutex_unlock(&glob->m_is_running);
}

int	sim_is_running(t_glob *glob)
{
	int	result;

	pthread_mutex_lock(&glob->m_is_running);
	result = glob->is_running;
	pthread_mutex_unlock(&glob->m_is_running);
	return (result);
}

int	check_eatcount(t_philo *philos, int len, int meals)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_lock(&philos[i].mutex);
		if (philos[i].meal_count < meals)
		{
			pthread_mutex_unlock(&philos[i].mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].mutex);
		i++;
	}
	return (1);
}
