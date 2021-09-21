/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:12:23 by adesvall          #+#    #+#             */
/*   Updated: 2021/09/22 01:36:33 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define M_EAT " is eating\n"
# define M_SLEEP " is sleeping\n"
# define M_THINK " is thinking\n"
# define M_FORK " has taken a fork\n"
# define M_DIED " died\n"
# define M_STOP "number of times each philosopher must eat has been reached\n"

typedef struct s_glob	t_glob;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	uint64_t		last_meal;
	pthread_mutex_t	mutex;
	t_glob			*glob;
}						t_philo;

typedef struct s_glob
{
	int				n_philo;
	t_philo			*philos;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	int				n_meals;
	uint64_t		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	end;

}						t_glob;

int			init(t_glob *glob, int argc, char **argv);
void		*philo_life(void *vphilo);
void		display(t_glob *glob, int id, char *str);

int			ft_strlen(char *str);
int			ft_atoi(const char *str);
void		ft_putnbr_fd(int n, int fd);
uint64_t	get_time(void);

#endif