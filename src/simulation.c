/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:53 by aschmidt          #+#    #+#             */
/*   Updated: 2024/09/05 12:40:50 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*session;

	philo = (t_philosopher *)arg;
	session = philo->simulation;
	while (1)
	{
		pthread_mutex_lock(&session->run_mutex);
		if (!session->run_simulation)
		{
			pthread_mutex_unlock(&session->run_mutex);
			break ;
		}
		pthread_mutex_unlock(&session->run_mutex);
		if (session->number_philos != 1)
		{
			print_state(session, philo->id, "is thinking");
			philo_think(philo);
		}
		if (!philo_eat(philo) || are_full(session))
			return (NULL);
		print_state(session, philo->id, "is sleeping");
		run_timer(philo, session->time_to_sleep);
	}
	return (NULL);
}

void	control_simulation(t_simulation *session)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&session->run_mutex);
		if (!session->run_simulation)
		{
			pthread_mutex_unlock(&session->run_mutex);
			break ;
		}
		pthread_mutex_unlock(&session->run_mutex);
		i = 0;
		while (i < session->number_philos)
		{
			if (!is_alive(&session->philos[i]))
				break ;
			if (are_full(session))
				break ;
			i++;
		}
		usleep(1000);
	}
	return ;
}

void	start_simulation(t_simulation *session)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	session->start_time = get_timestamp();
	while (i < session->number_philos)
	{
		pthread_create(&session->philos[i].thread_id, \
				NULL, &philo_routine, &session->philos[i]);
		i++;
	}
	control_simulation(session);
	while (j < session->number_philos)
	{
		pthread_join(session->philos[j].thread_id, NULL);
		j++;
	}
}
