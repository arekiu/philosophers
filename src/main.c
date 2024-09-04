/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:53:22 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/21 12:36:58 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_mutex(t_simulation *sesion)
{
	pthread_mutex_init(&sesion->run_mutex, NULL);
	pthread_mutex_init(&sesion->log_mutex, NULL);
}

void	set_data(t_simulation *sesion, char *argv[])
{
	int	i;

	i = 0;
	sesion->number_philos = ft_atoi(argv[1]);
	sesion->time_to_die = ft_atoi(argv[2]);
	sesion->time_to_eat = ft_atoi(argv[3]);
	sesion->time_to_sleep = ft_atoi(argv[4]);
	sesion->run_simulation = 1;
	init_mutex(sesion);
	if (argv[5])
		sesion->max_meals = ft_atoi(argv[5]);
	else
		sesion->max_meals = -1;
	sesion->forks = malloc(sizeof(t_fork) * sesion->number_philos);
	if (!sesion->forks)
		return ;
	while (i < sesion->number_philos)
	{
		sesion->forks[i].fork_id = i;
		pthread_mutex_init(&sesion->forks[i].mutex, NULL);
		i++;
	}
	sesion->philos = malloc(sizeof(t_philosopher) * sesion->number_philos);
	if (!sesion->philos)
		return ;
}

void	set_philos(t_simulation *sesion)
{
	int	i;

	i = 0;
	while (i < sesion->number_philos)
	{
		sesion->philos[i].id = i + 1;
		sesion->philos[i].left_fork = &sesion->forks[i];
		if (i == sesion->number_philos - 1)
			sesion->philos[i].right_fork = &sesion->forks[0];
		else
			sesion->philos[i].right_fork = &sesion->forks[i + 1];
		sesion->philos[i].last_meal = get_timestamp();
		sesion->philos[i].meals_eaten = 0;
		sesion->philos[i].simulation = sesion;
		pthread_mutex_init(&sesion->philos[i].action_mutex, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_simulation	sesion;

	if (argc == 5 || argc == 6)
	{
		if (!is_valid(argc, argv))
			return (1);
		else
		{
			set_data(&sesion, argv);
			set_philos(&sesion);
			start_simulation(&sesion);
			clean_sesion(&sesion);
		}
	}
	else
	{
		printf("Invalid number of arguments\n ");
		return (1);
	}
	return (0);
}
