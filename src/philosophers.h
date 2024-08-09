/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:49:06 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/01 15:49:16 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_simulation
{
    int     number_philos;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     max_meals;
    long    start_time;
    int     end_simulation;
    t_fork  *forks;
    t_philosopher *philosophers;
}       t_simulation;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int             fork_id;
}                   t_fork;


typedef struct s_philosopher
{
    int         id;
    int         meals;
    int         max_meals;
    long        last_meal;
    t_fork      *left_fork;
    t_fork      *right_fork;
    pthread_t   thread_id;
    t_simulation    *simulation;
}               t_philosopher;

int is_valid(int argc, char *argv[]);

#endif
