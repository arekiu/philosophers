/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:45 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/21 10:38:04 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_timestamp(void)
{
	struct timeval	tv;
	long long		timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (timestamp);
}

void	print_state(t_simulation *sesion, int id, const char *state)
{
	long long	current_time;
	long long	elapsed_time;

	current_time = get_timestamp();
	elapsed_time = current_time - sesion->start_time;
	printf("%lld %d %s\n", elapsed_time, id, state);
}

void	clean_sesion(t_simulation *sesion)
{
	int	i;

	i = 0;
	while (i < sesion->number_philos)
	{
		pthread_mutex_destroy(&sesion->forks[i].mutex);
		i++;
	}
	free(sesion->forks);
	free(sesion->philos);
}
