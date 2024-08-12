/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:53:22 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/12 15:24:13 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_data(t_simulation *sesion, char *argv[])
{
	sesion->number_philos = ft_atoi(argv[1]);
	sesion->time_to_die = ft_atoi(argv[2]);
	sesion->time_to_eat = ft_atoi(argv[3]);
	sesion->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sesion->max_meals = ft_atoi(argv[5]);
	else
		sesion->max_meals = -1;
}

int	main(int argc, char *argv[])
{
	t_simulation	sesion;

	if (argc == 5 || argc == 6)
	{
		if (!is_valid(argc, argv))
		{
			printf("Invalid arguments\n");
			return (0);
		}
		else
		{
			printf("Todo bien!\n");
			set_data(&sesion, argv);
			printf("Time to die: %d\n", sesion.time_to_die);
			printf("Max meals: %d\n", sesion.max_meals);
		}
	}
	else
	{
		printf("Invalid number of arguments\n");
		return (0);
	}
	return (0);
}
