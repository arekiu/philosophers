/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:45 by aschmidt          #+#    #+#             */
/*   Updated: 2024/09/05 12:40:47 by aschmidt         ###   ########.fr       */
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

void	print_state(t_simulation *session, int id, const char *state)
{
	long long	current_time;
	long long	elapsed_time;
	int			running;

	current_time = get_timestamp();
	elapsed_time = current_time - session->start_time;
	pthread_mutex_lock(&session->run_mutex);
	running = session->run_simulation;
	pthread_mutex_unlock(&session->run_mutex);
	pthread_mutex_lock(&session->log_mutex);
	if (running == 0 && ft_strncmp(state, "died", 4) != 0)
	{
		pthread_mutex_unlock(&session->log_mutex);
		return ;
	}
	printf("%lld %d %s\n", elapsed_time, id, state);
	pthread_mutex_unlock(&session->log_mutex);
}

void	clean_session(t_simulation *session)
{
	int	i;

	i = 0;
	while (i < session->number_philos)
	{
		pthread_mutex_destroy(&session->forks[i].mutex);
		pthread_mutex_destroy(&session->philos[i].action_mutex);
		i++;
	}
	pthread_mutex_destroy(&session->run_mutex);
	pthread_mutex_destroy(&session->log_mutex);
	free(session->forks);
	free(session->philos);
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

void	run_timer(t_philosopher *philo, long miliseconds)
{
	long long	start_time;
	long long	current_time;
	long long	end_time;

	start_time = get_timestamp();
	end_time = start_time + miliseconds;
	current_time = start_time;
	while (current_time < end_time)
	{
		usleep(100);
		if (current_time - philo->last_meal > philo->simulation->time_to_die)
			break ;
		current_time = get_timestamp();
	}
}
