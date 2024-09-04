/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:53 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/22 15:26:51 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sesion;

	philo = (t_philosopher *)arg;
	sesion = philo->simulation;
	while (1)
	{
		pthread_mutex_lock(&sesion->run_mutex);
        if (!sesion->run_simulation)
        {
            pthread_mutex_unlock(&sesion->run_mutex);
            break;
        }
        pthread_mutex_unlock(&sesion->run_mutex);
		print_state(sesion, philo->id, "is thinking");
		philo_think(philo);
		if (!philo_eat(philo))
			return (NULL);
        print_state(sesion, philo->id, "is sleeping");
		run_timer(philo, sesion->time_to_sleep);
	}
	return (NULL);
}

void	control_simulation(t_simulation *sesion)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&sesion->run_mutex);
        if (!sesion->run_simulation)
        {
            pthread_mutex_unlock(&sesion->run_mutex);
            break;
        }
        pthread_mutex_unlock(&sesion->run_mutex);
		i = 0;
		while (i < sesion->number_philos)
		{
			if (!is_alive(&sesion->philos[i]))
				break ;
			if (are_full(sesion))
				break ;
			i++;
		}
		usleep(1000);
	}
	return ;
}

void	start_simulation(t_simulation *sesion)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
    sesion->start_time = get_timestamp();
	while (i < sesion->number_philos)
	{
		pthread_create(&sesion->philos[i].thread_id, \
				NULL, &philo_routine, &sesion->philos[i]);
		i++;
	}
	control_simulation(sesion);
	while (j < sesion->number_philos)
	{
		pthread_join(sesion->philos[j].thread_id, NULL);
		j++;
	}
}
