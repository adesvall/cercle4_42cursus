/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:17:08 by adesvall          #+#    #+#             */
<<<<<<< HEAD:philo/srcs/init.c
/*   Updated: 2021/11/23 18:28:29 by adesvall         ###   ########.fr       */
=======
/*   Updated: 2021/11/21 15:01:59 by adesvall         ###   ########.fr       */
>>>>>>> c8511393e5df2d08d2c7fed33e289bddabd94717:philosophers/srcs/init.c
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_glob *glob)
{
	int	i;

	pthread_mutex_init(&glob->write, NULL);
	pthread_mutex_init(&glob->m_is_running, NULL);
	glob->forks = malloc(glob->n_philo * sizeof(pthread_mutex_t));
	if (!glob->forks)
		return (-1);
	i = 0;
	while (i < glob->n_philo)
	{
		pthread_mutex_init(&glob->forks[i], NULL);
		if (i % 2 == 0)
		{
			glob->philos[i].fork1 = &glob->forks[i];
			glob->philos[i].fork2 = &glob->forks[(i + 1) % glob->n_philo];
		}
		else
		{
			glob->philos[i].fork1 = &glob->forks[(i + 1) % glob->n_philo];
			glob->philos[i].fork2 = &glob->forks[i];
		}
		i++;
	}
	return (0);
}

void	init_philos(t_glob *glob)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < glob->n_philo)
	{
		philo = &glob->philos[i];
		memset(philo, 0, sizeof(t_philo));
		philo->id = i;
		philo->glob = glob;
		pthread_mutex_init(&philo->mutex, NULL);
		i++;
	}
}

int	wrong_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isin(argv[i][j], "0123456789"))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init(t_glob *glob, int argc, char **argv)
{
	memset(glob, 0, sizeof(t_glob));
	glob->n_meals = -1;
	if (wrong_arg(argc, argv) ||
	!ft_atoi_with_overflow_check(argv[1], &glob->n_philo) ||
	!ft_atoi_with_overflow_check(argv[2], &glob->time_die) ||
	!ft_atoi_with_overflow_check(argv[3], &glob->time_eat) ||
	!ft_atoi_with_overflow_check(argv[4], &glob->time_sleep) ||
	(argc == 6 && !ft_atoi_with_overflow_check(argv[5], &glob->n_meals)))
	{
		printf("Bad arguments. Must be positive integers.\n");
		return (-1);
	}
	glob->is_running = 1;
<<<<<<< HEAD:philo/srcs/init.c
=======
	if (argc == 6)
		glob->n_meals = ft_atoi(argv[5]);
>>>>>>> c8511393e5df2d08d2c7fed33e289bddabd94717:philosophers/srcs/init.c
	glob->philos = malloc(glob->n_philo * sizeof(t_philo));
	if (!glob->philos)
		return (-1);
	init_philos(glob);
	return (init_mutexes(glob));
}

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
			pthread_mutex_destroy(&glob->philos[i++].mutex);
		free(glob->philos);
	}
	pthread_mutex_destroy(&glob->write);
	pthread_mutex_destroy(&glob->m_is_running);
	return (1);
}
