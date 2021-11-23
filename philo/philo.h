/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:12:23 by adesvall          #+#    #+#             */
/*   Updated: 2021/11/23 18:15:31 by adesvall         ###   ########.fr       */
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
# define M_STOP "Every philosopher has eaten enough\n"

typedef struct s_glob	t_glob;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	uint64_t		last_meal;
	pthread_mutex_t	mutex;
	t_glob			*glob;
	pthread_mutex_t *fork1;
	pthread_mutex_t	*fork2;
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
	int				is_running;
	pthread_mutex_t	m_is_running;
}						t_glob;

int			init(t_glob *glob, int argc, char **argv);
void		*philo_life(void *vphilo);
void		display(t_glob *glob, int id, char *str);
int			sim_is_running(t_glob *glob);
int			check_eatcount(t_philo *philos, int len, int meals);
void		stop_sim(t_glob *glob);
int			clean_glob(t_glob *glob);

int			ft_strlen(char *str);
int			ft_isin(char c, const char *str);
int			ft_atoi_with_overflow_check(const char *str, int *n);
void		ft_putnbr_fd(int n, int fd);
uint64_t	get_time(void);

#endif