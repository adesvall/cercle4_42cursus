/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:17:08 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/20 15:33:32 by adesvall         ###   ########.fr       */
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

int	init(t_glob *glob, int argc, char **argv)
{
	memset(glob, 0, sizeof(t_glob));
	glob->n_philo = ft_atoi(argv[1]);
	glob->time_die = ft_atoi(argv[2]);
	glob->time_eat = ft_atoi(argv[3]);
	glob->time_sleep = ft_atoi(argv[4]);
	glob->is_running = 1;
	if (argc == 6)
		glob->n_meals = ft_atoi(argv[5]);
	// GERER LES ERREURS D'ENTREE
	glob->philos = malloc(glob->n_philo * sizeof(t_philo));
	if (!glob->philos)
		return (-1);
	init_philos(glob);
	return (init_mutexes(glob));
}
