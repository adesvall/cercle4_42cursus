/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:39:20 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/20 17:28:52 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->glob->forks;
	pthread_mutex_lock(&forks[philo->id]);
	display(philo->glob, philo->id, M_FORK);
	if (philo->glob->n_philo != 1)
	{
		pthread_mutex_lock(&forks[(philo->id + 1) % philo->glob->n_philo]);
		display(philo->glob, philo->id, M_FORK);
	}
	else
	{
		while (sim_is_running(philo->glob)) { usleep(100); }
	}
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
	pthread_mutex_t	*forks;

	forks = philo->glob->forks;
	pthread_mutex_unlock(&forks[philo->id]);
	pthread_mutex_unlock(&forks[(philo->id + 1) % philo->glob->n_philo]);
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
	if (pthread_create(&tid, NULL, philo_monitor, vphilo))
		return ((void *)1);
	//pthread_detach(tid);
	philo->last_meal = philo->glob->start;
	while (sim_is_running(philo->glob))
	{
		take_forks(philo);
		eat(philo);
		drop_forks_and_sleep(philo);
		display(philo->glob, philo->id, M_THINK);
	}
	printf("%d loop OK\n", philo->id);
	pthread_join(tid, NULL);
	printf("%d monitor OK\n", philo->id);
	return (NULL);
}
