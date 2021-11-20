/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:11:00 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/20 17:52:15 by adesvall         ###   ########.fr       */
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
	pthread_mutex_destroy(&glob->m_is_running);
	return (1);
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

void	*global_monitor(void *vglob)
{
	t_glob	*glob;

	glob = (t_glob *)vglob;
	while (sim_is_running(glob))
	{
		usleep(glob->time_eat * 1000);
		if (check_eatcount(glob->philos, glob->n_philo, glob->n_meals))
		{
			display(glob, -1, M_STOP);
			stop_sim(glob);
			return (NULL);
		}
	}
	return (NULL);
}

void	join_threads(t_glob *glob, pthread_t *tid)
{
	int	i;

	i = 0;
	if (!tid[0])
		i = 1;
	while (i < glob->n_philo + 1)
	{
		// printf("%d : TID : %lu\n", i, tid[i]);
		pthread_join(tid[i], NULL);
		i++;
	}
}

int	start_threads(t_glob *glob)
{
	int			i;
	int			j;
	pthread_t	tid[glob->n_philo + 1];

	tid[0] = 0;
	if (glob->n_meals > 0)
	{
		if (pthread_create(&tid[0], NULL, global_monitor, (void *)glob))
			return (-1);
		// pthread_detach(tid);
	}
	glob->start = get_time();
	j = 0;
	while (j < 2)
	{
		i = 0;
		while (2 * i + j < glob->n_philo)
		{
			if (pthread_create(&tid[1 + 2 * i + j], NULL, philo_life, \
									(void *)&glob->philos[2 * i + j]))
				return (-1);
			i++;
			// pthread_detach(tid);
		}
		usleep(glob->time_eat * 500);
		j++;
	}
	join_threads(glob, tid);
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
	
	
	
	pthread_mutex_unlock(&glob.write);
	clean_glob(&glob);
}

/*
test 200 100 100 
et attention au message apres message de fin okOKOK
peut etre ttention a unlock tout les mutexes
*/ 