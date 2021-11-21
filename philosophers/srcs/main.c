/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:11:00 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/21 15:09:37 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_join(tid[i], NULL);
		i++;
	}
}

int	start_threads(t_glob *glob, pthread_t *tid)
{
	int		i;
	int		j;

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
		}
		usleep(glob->time_eat * 500);
		j++;
	}
	return (0);
}

int	start_sim(t_glob *glob)
{
	pthread_t	*tid;

	tid = malloc(sizeof(pthread_t) * (glob->n_philo + 1));
	if (!tid)
		return (-1);
	tid[0] = 0;
	if (glob->n_meals > 0)
		if (pthread_create(&tid[0], NULL, global_monitor, (void *)glob))
			return (-1);
	glob->start = get_time();
	if (start_threads(glob, tid))
		return (-1);
	join_threads(glob, tid);
	free(tid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_glob	glob;

	if (argc != 6 && argc != 5)
		return (0);
	if (init(&glob, argc, argv))
		return (clean_glob(&glob));
	if (start_sim(&glob))
		return (clean_glob(&glob));
	clean_glob(&glob);
}
