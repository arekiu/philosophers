/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:45 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/21 12:43:46 by aschmidt         ###   ########.fr       */
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
	int			running;

	current_time = get_timestamp();
	elapsed_time = current_time - sesion->start_time;
	pthread_mutex_lock(&sesion->run_mutex);
	running = sesion->run_simulation;
	pthread_mutex_unlock(&sesion->run_mutex);
	pthread_mutex_lock(&sesion->log_mutex);
	if (running == 0 && ft_strncmp(state, "died", 4) != 0)
	{
		pthread_mutex_unlock(&sesion->log_mutex);
		return ;
	}
	printf("%lld %d %s\n", elapsed_time, id, state);
	pthread_mutex_unlock(&sesion->log_mutex);
}

void	clean_sesion(t_simulation *sesion)
{
	int	i;

	i = 0;
	while (i < sesion->number_philos)
	{
		pthread_mutex_destroy(&sesion->forks[i].mutex);
		pthread_mutex_destroy(&sesion->philos[i].action_mutex);
		i++;
	}
	pthread_mutex_destroy(&sesion->run_mutex);
	pthread_mutex_destroy(&sesion->log_mutex);
	free(sesion->forks);
	free(sesion->philos);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	st1;
	unsigned char	st2;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		st1 = (unsigned char)s1[i];
		st2 = (unsigned char)s2[i];
		if (st1 == st2)
		{
			i++;
		}
		else
		{
			return (st1 - st2);
		}
	}
	return (0);
}
