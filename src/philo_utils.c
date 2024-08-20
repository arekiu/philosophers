/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:35 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/20 16:09:46 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_alive(t_philosopher *philo)
{
	long long	time_without_eating;

	time_without_eating = get_timestamp() - philo->last_meal;
	if (time_without_eating > philo->simulation->time_to_die)
	{
		philo->simulation->run_simulation = 0;
		print_state(philo->simulation, philo->id, "died");
        return (0);
	}
	return (1);
}

int	is_full(t_philosopher *philo)
{
	if (philo->meals_eaten == philo->simulation->max_meals)
	{
		philo->simulation->run_simulation = 0;
		return (1);
	}
	return (0);
}
