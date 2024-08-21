/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:35 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/21 10:25:20 by aschmidt         ###   ########.fr       */
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

static void	take_forks(t_philosopher *philo)
{
	long long	last_meal_time;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_state(philo->simulation, philo->id, "has taken a fork");
		usleep(100);
		pthread_mutex_lock(&philo->right_fork->mutex);
		last_meal_time = get_timestamp() - philo->last_meal;
		if (last_meal_time < philo->simulation->time_to_die)
			print_state(philo->simulation, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_state(philo->simulation, philo->id, "has taken a fork");
		usleep(100);
		pthread_mutex_lock(&philo->left_fork->mutex);
		last_meal_time = get_timestamp() - philo->last_meal;
		if (last_meal_time < philo->simulation->time_to_die)
			print_state(philo->simulation, philo->id, "has taken a fork");
	}
	return ;
}

int	philo_eat(t_philosopher *philo)
{
	if (philo->simulation->number_philos == 1)
	{
		print_state(philo->simulation, philo->id, "has taken a fork");
		return (0);
	}
	take_forks(philo);
	if (philo->simulation->run_simulation)
	{
		print_state(philo->simulation, philo->id, "is eating");
		philo->last_meal = get_timestamp();
		philo->meals_eaten++;
		usleep(philo->simulation->time_to_eat * 1000);
	}
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	if (!philo->simulation->run_simulation)
		return (0);
	return (1);
}
