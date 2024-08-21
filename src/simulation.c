/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:53 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/21 11:34:06 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sesion;

	philo = (t_philosopher *)arg;
	sesion = philo->simulation;
	while (sesion->run_simulation)
	{
		if (!philo_eat(philo))
			return (NULL);
		print_state(sesion, philo->id, "is sleeping");
		usleep(sesion->time_to_sleep * 1000);
		if (!philo->simulation->run_simulation)
			return (NULL);
		print_state(sesion, philo->id, "is thinking");
		if (!philo->simulation->run_simulation)
			return (NULL);
	}
	return (NULL);
}

void	control_simulation(t_simulation *sesion)
{
	int	i;

	while (sesion->run_simulation)
	{
		i = 0;
		while (i < sesion->number_philos)
		{
			if (!is_alive(&sesion->philos[i]))
				break ;
			if (is_full(&sesion->philos[i]))
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
