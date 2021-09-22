/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:11:00 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/22 14:34:55 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_glob(t_glob *glob)
{
	int	i;

	if (glob->forks)
	{
		i = 0;
		while (i < glob->n_philo)
			pthread_mutex_destroy(&glob->forks[i++]);
		free(glob->forks);
	}
	if (glob->philos)
	{
		i = 0;
		while (i < glob->n_philo)
		{
			pthread_mutex_destroy(&glob->philos[i++].mutex);
		}
		free(glob->philos);
	}
	pthread_mutex_destroy(&glob->write);
	pthread_mutex_destroy(&glob->end);
	return (1);
}

int	check_eatcount(t_philo *philos, int len, int meals)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (philos[i].meal_count < meals)
			return (0);
		i++;
	}
	return (1);
}

void	*global_monitor(void *vglob)
{
	t_glob	*glob;

	glob = (t_glob *)vglob;
	while (1)
	{
		if (check_eatcount(glob->philos, glob->n_philo, glob->n_meals))
		{
			display(glob, -1, M_STOP);
			pthread_mutex_lock(&glob->write);
			pthread_mutex_unlock(&glob->end);
			return (NULL);
		}
		usleep(glob->time_eat * 1000);
	}
}

int	start_threads(t_glob *glob)
{
	int			i;
	int			j;
	pthread_t	tid;

	if (glob->n_meals > 0)
	{
		if (pthread_create(&tid, NULL, global_monitor, (void *)glob))
			return (-1);
		pthread_detach(tid);
	}
	glob->start = get_time();
	j = 0;
	while (j < 2)
	{
		i = 0;
		while (2 * i + j < glob->n_philo)
		{
			if (pthread_create(&tid, NULL, philo_life, \
									(void *)&glob->philos[2 * i++ + j]))
				return (-1);
			pthread_detach(tid);
		}
		usleep(glob->time_eat * 500);
		j++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_glob	glob;

	if (argc != 6 && argc != 5)
		return (0);
	if (init(&glob, argc, argv))
		return (clean_glob(&glob));
	if (start_threads(&glob))
		return (clean_glob(&glob));
	pthread_mutex_lock(&glob.end);
	pthread_mutex_unlock(&glob.end);
	clean_glob(&glob);
}
