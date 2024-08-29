/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:35 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/22 17:39:01 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_alive(t_philosopher *philo)
{
	long long	time_without_eating;

	pthread_mutex_lock(&philo->simulation->run_mutex);
	if (philo->meals_eaten == philo->simulation->max_meals)
	{
		pthread_mutex_unlock(&philo->simulation->run_mutex);
		return (1);
	}
	time_without_eating = get_timestamp() - philo->last_meal;
	if (time_without_eating >= philo->simulation->time_to_die)
	{
		philo->simulation->run_simulation = 0;
		print_state(philo->simulation, philo->id, "died");
		pthread_mutex_unlock(&philo->simulation->run_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->simulation->run_mutex);
	return (1);
}

int	are_full(t_simulation *sesion)
{
	int	i;

	i = 0;
	while (i < sesion->number_philos)
	{
		if (sesion->philos[i].meals_eaten != sesion->max_meals)
			return (0);
		i++;
	}
	sesion->run_simulation = 0;
	return (1);
}

static void	take_forks(t_philosopher *philo)
{
	if (!philo->simulation->run_simulation)
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->simulation->run_simulation)
			print_state(philo->simulation, philo->id, "has taken a fork");
		usleep(100);
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (philo->simulation->run_simulation)
			print_state(philo->simulation, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (philo->simulation->run_simulation)
			print_state(philo->simulation, philo->id, "has taken a fork");
		usleep(100);
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->simulation->run_simulation)
			print_state(philo->simulation, philo->id, "has taken a fork");
	}
	return ;
}

int	philo_eat(t_philosopher *philo)
{
	if (philo->simulation->number_philos == 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_state(philo->simulation, philo->id, "has taken a fork");
		pthread_mutex_unlock(&philo->left_fork->mutex);
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

void philo_think(t_philosopher *philo)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	if (philo->simulation->number_philos % 2 == 0)
		return ;
	time_to_eat = philo->simulation->time_to_eat;
	time_to_sleep = philo->simulation->time_to_sleep;
	time_to_think = (time_to_eat * 2) - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	usleep(time_to_think * 1000 * 0.3);
}
