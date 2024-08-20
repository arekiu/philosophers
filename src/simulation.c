/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:53 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/20 16:08:57 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void take_forks(t_philosopher *philo)
{
    if (!philo->simulation->run_simulation || !is_alive(philo))
            return;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->left_fork->mutex);
        print_state(philo->simulation, philo->id, "has taken a fork");
        usleep(100);
        if (!philo->simulation->run_simulation || !is_alive(philo))
            return;
        pthread_mutex_lock(&philo->right_fork->mutex);
        print_state(philo->simulation, philo->id, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->right_fork->mutex);
        print_state(philo->simulation, philo->id, "has taken a fork");
        usleep(100);
        if (!philo->simulation->run_simulation || !is_alive(philo))
            return;
        pthread_mutex_lock(&philo->left_fork->mutex);
        print_state(philo->simulation, philo->id, "has taken a fork");
    }
    return ;
}

void    *philo_routine(void *arg)
{
    t_philosopher *philo;
    t_simulation   *sesion;

    philo = (t_philosopher *)arg;
    sesion = philo->simulation;
    while (sesion->run_simulation)
    {
        if (!philo->simulation->run_simulation)
            return (NULL);
        take_forks(philo);
        print_state(sesion, philo->id, "is eating");
        philo->last_meal = get_timestamp();
        philo->meals_eaten++;
        if (!philo->simulation->run_simulation)
            return (NULL);
        usleep(sesion->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->left_fork->mutex);
        pthread_mutex_unlock(&philo->right_fork->mutex);
        if (!philo->simulation->run_simulation)
            return (NULL);
        print_state(sesion, philo->id, "is sleeping");
        usleep(sesion->time_to_sleep * 1000);
        if (!philo->simulation->run_simulation)
            return (NULL);
        print_state(sesion, philo->id, "is thinking");
    }
    return (NULL);
}

void    control_simulation(t_simulation *sesion)
{
    int i;

    while (sesion->run_simulation)
    {
        i = 0;
        while (i < sesion->number_philos)
        {
            if (!is_alive(&sesion->philos[i]))
                break ;
            if (is_full(&sesion->philos[i]))
                break;
            i++;
        }
        //usleep(1000);
    }
    return ;
}

void    start_simulation(t_simulation *sesion)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < sesion->number_philos)
    {
        pthread_create(&sesion->philos[i].thread_id, NULL, &philo_routine, &sesion->philos[i]);
        i++;
    }
    control_simulation(sesion);
    while (j < sesion->number_philos)
    {
        pthread_join(sesion->philos[j].thread_id, NULL);
        j++;
    }
}
