/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:17:08 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/09 23:52:33 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_glob *glob)
{
	int	i;

	pthread_mutex_init(&glob->write, NULL);
	pthread_mutex_init(&glob->end, NULL);
	pthread_mutex_lock(&glob->end);
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

int check_args(t_glob *glob, int ac)
{
	if (glob->n_philo <= 0 || glob->time_die < 60)
		return (1);
	if (glob->time_eat < 60 || glob->time_sleep < 60)
		return (1);
	if (ac == 6 && glob->n_meals <= 0)
		return (1);
	return (0);
}

int	init(t_glob *glob, int argc, char **argv)
{
	memset(glob, 0, sizeof(t_glob));
	glob->n_philo = ft_atoi(argv[1]);
	glob->time_die = ft_atoi(argv[2]);
	glob->time_eat = ft_atoi(argv[3]);
	glob->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		glob->n_meals = ft_atoi(argv[5]);
	if (check_args(glob, argc))
	{
		write(1, "Error: Bad arguments\n", 21);
		return (1);
	}
	glob->philos = malloc(glob->n_philo * sizeof(t_philo));
	if (!glob->philos)
		return (1);
	init_philos(glob);
	return (init_mutexes(glob));
}
