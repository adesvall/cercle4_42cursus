/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:11:00 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/21 21:05:45 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_glob *glob)
{
	int	i;
	pthread_t tid;

	i = 0;
	while (i < glob->n_philo)
	{
		if (pthread_create(&tid, NULL, philo_life, (void *)&glob->philos[i]))
			return (-1);
		pthread_detach(tid);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_glob	glob;

	if (argc != 6 || argc != 5)
		return (0);
	if (init(&glob, argc, argv))
		return (1); //clean_glob(&glob)
	if (start_threads(&glob))
		return (1);
	pthread_mutex_lock(&glob.end);
	//clean_glob(&glob);
}
