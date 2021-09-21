/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:12:23 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/21 21:01:53 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef unsigned int uint64_t;
typedef struct s_glob t_glob;
typedef struct s_philo
{
	int				id;
	uint64_t		last_meal;
	pthread_mutex_t	mutex;
	t_glob			*glob;
}	t_philo;

typedef struct s_glob
{
	int				n_philo;
	t_philo			*philos;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	int				n_meals;
	time_t			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	end;

}	t_glob;

int			init(t_glob *glob, int argc, char **argv);
void		*philo_life(void *vphilo);
int			ft_atoi(const char *str);
uint64_t	get_time(void);

#endif