/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:53:22 by aschmidt          #+#    #+#             */
/*   Updated: 2024/09/05 12:40:42 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_mutex(t_simulation *session)
{
	pthread_mutex_init(&session->run_mutex, NULL);
	pthread_mutex_init(&session->log_mutex, NULL);
}

void	set_data(t_simulation *session, char *argv[])
{
	int	i;

	i = 0;
	session->number_philos = ft_atoi(argv[1]);
	session->time_to_die = ft_atoi(argv[2]);
	session->time_to_eat = ft_atoi(argv[3]);
	session->time_to_sleep = ft_atoi(argv[4]);
	session->run_simulation = 1;
	init_mutex(session);
	if (argv[5])
		session->max_meals = ft_atoi(argv[5]);
	else
		session->max_meals = -1;
	session->forks = malloc(sizeof(t_fork) * session->number_philos);
	if (!session->forks)
		return ;
	while (i < session->number_philos)
	{
		session->forks[i].fork_id = i;
		pthread_mutex_init(&session->forks[i].mutex, NULL);
		i++;
	}
	session->philos = malloc(sizeof(t_philosopher) * session->number_philos);
	if (!session->philos)
		return ;
}

void	set_philos(t_simulation *session)
{
	int	i;

	i = 0;
	while (i < session->number_philos)
	{
		session->philos[i].id = i + 1;
		session->philos[i].left_fork = &session->forks[i];
		if (i == session->number_philos - 1)
			session->philos[i].right_fork = &session->forks[0];
		else
			session->philos[i].right_fork = &session->forks[i + 1];
		session->philos[i].last_meal = get_timestamp();
		session->philos[i].meals_eaten = 0;
		session->philos[i].simulation = session;
		pthread_mutex_init(&session->philos[i].action_mutex, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_simulation	session;

	if (argc == 5 || argc == 6)
	{
		if (!is_valid(argc, argv))
			return (1);
		else
		{
			set_data(&session, argv);
			set_philos(&session);
			start_simulation(&session);
			clean_session(&session);
		}
	}
	else
	{
		printf("Invalid number of arguments\n ");
		return (1);
	}
	return (0);
}
