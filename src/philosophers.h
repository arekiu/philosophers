/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:49:06 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/20 15:54:53 by aschmidt         ###   ########.fr       */
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

typedef struct s_philosopher    t_philosopher;

typedef struct s_fork
{
    pthread_mutex_t mutex;
    int             fork_id;
}                   t_fork;

typedef struct s_simulation
{
    int     number_philos;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     max_meals;
    long long    start_time;
    int     run_simulation;
    t_fork  *forks;
    t_philosopher *philos;
}       t_simulation;

typedef struct s_philosopher
{
    int         id;
    int         meals_eaten;
    long long        last_meal;
    t_fork      *left_fork;
    t_fork      *right_fork;
    pthread_t   thread_id;
    t_simulation    *simulation;
}               t_philosopher;

int         is_valid(int argc, char *argv[]);
int         ft_atoi(const char *str);
long long	ft_atoll(const char *str);
long long   get_timestamp();
void        print_state(t_simulation *sesion, int id, const char *state);
void        clean_sesion(t_simulation *sesion);
void        start_simulation(t_simulation *sesion);
void        control_simulation(t_simulation *sesion);
void        *philo_routine(void *arg);
int         is_alive(t_philosopher *philo);
int         is_full(t_philosopher *philo);

#endif
