/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:49:06 by aschmidt          #+#    #+#             */
/*   Updated: 2024/09/05 12:48:38 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher	t_philosopher;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				fork_id;
}	t_fork;

typedef struct s_simulation
{
	int				number_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long long		start_time;
	int				run_simulation;
	pthread_mutex_t	run_mutex;
	pthread_mutex_t	log_mutex;
	t_fork			*forks;
	t_philosopher	*philos;
}	t_simulation;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_simulation	*simulation;
	pthread_mutex_t	action_mutex;
}	t_philosopher;

int			is_valid(int argc, char *argv[]);
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
long long	get_timestamp(void);
void		print_state(t_simulation *session, int id, const char *state);
void		clean_session(t_simulation *session);
void		start_simulation(t_simulation *session);
void		control_simulation(t_simulation *session);
void		*philo_routine(void *arg);
int			is_alive(t_philosopher *philo);
int			are_full(t_simulation *session);
int			philo_eat(t_philosopher *philo);
void		philo_think(t_philosopher *philo);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		run_timer(t_philosopher *philo, long miliseconds);

# define GREEN "\e[0;32m"
# define RED "\e[0;31m"
# define YELLOW "\e[1;33m"
# define RESET "\e[0m"

#endif
