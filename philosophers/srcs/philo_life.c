/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:39:20 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/21 20:58:02 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->glob->forks;
	pthread_mutex_lock(&forks[philo->id]);
	//displog
	pthread_mutex_lock(&forks[(philo->id + 1) % philo->glob->n_philo]);
	//displog
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time();
	//displaylog
	usleep(philo->glob->time_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
}

void	pose_forks_and_sleep(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->glob->forks;
	pthread_mutex_unlock(&forks[philo->id]);
	pthread_mutex_unlock(&forks[(philo->id + 1) % philo->glob->n_philo]);
	//displog
	usleep(philo->glob->time_sleep * 1000);
}

void	*philo_life(void *vphilo)
{
	t_philo	*philo;

	philo = (t_philo *)vphilo;
	philo->last_meal = get_time();
	while (1)
	{
		take_forks(philo);
		eat(philo);
		pose_forks_and_sleep(philo);
		//displaylog
	}
	return (NULL);
}
