/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:39:20 by adesvall          #+#    #+#             */
/*   Updated: 2021/12/01 16:23:16 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	display(philo->glob, philo->id, M_FORK);
	if (philo->glob->n_philo != 1)
	{
		pthread_mutex_lock(philo->fork2);
		display(philo->glob, philo->id, M_FORK);
	}
	else
		while (sim_is_running(philo->glob))
			usleep(100);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time();
	display(philo->glob, philo->id, M_EAT);
	usleep(philo->glob->time_eat * 1000);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->mutex);
}

void	drop_forks_and_sleep(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork1);
	if (philo->glob->n_philo != 1)
		pthread_mutex_unlock(philo->fork2);
	display(philo->glob, philo->id, M_SLEEP);
	usleep(philo->glob->time_sleep * 1000);
}

void	*philo_monitor(void *vphilo)
{
	t_philo		*philo;

	philo = (t_philo *)vphilo;
	while (sim_is_running(philo->glob))
	{
		pthread_mutex_lock(&philo->mutex);
		if (get_time() > philo->last_meal + philo->glob->time_die)
		{
			display(philo->glob, philo->id, M_DIED);
			stop_sim(philo->glob);
			pthread_mutex_unlock(&philo->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(2000);
	}
	return (NULL);
}

void	*philo_life(void *vphilo)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)vphilo;
	philo->last_meal = philo->glob->start;
	if (pthread_create(&tid, NULL, philo_monitor, vphilo))
		return ((void *)1);
	while (sim_is_running(philo->glob))
	{
		take_forks(philo);
		eat(philo);
		drop_forks_and_sleep(philo);
		display(philo->glob, philo->id, M_THINK);
	}
	pthread_join(tid, NULL);
	return (NULL);
}
