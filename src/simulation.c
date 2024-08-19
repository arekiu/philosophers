#include "philosophers.h"

static void take_forks(t_philosopher *philo)
{
    if (philo->simulation->run_simulation == 0)
        return ;
    if (philo->id % 2 == 0) 
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        print_state(philo->simulation, philo->id, "has taken a fork");
        if (philo->simulation->run_simulation == 0)
            return ;
        pthread_mutex_lock(&philo->right_fork->fork);
        print_state(philo->simulation, philo->id, "has taken a fork");
    }
    else 
    {
        pthread_mutex_lock(&philo->right_fork->fork);
        print_state(philo->simulation, philo->id, "has taken a fork");
        if (philo->simulation->run_simulation == 0)
            return ;
        pthread_mutex_lock(&philo->left_fork->fork);
        print_state(philo->simulation, philo->id, "has taken a fork");
    }
    return ;
}

void    *philo_routine(void *arg)
{
    t_philosopher *philo;
    t_simulation   *sesion;

    philo = (t_philosopher *)arg;
    sesion = philo->simulation;
    while (sesion->run_simulation)
    {
        take_forks(philo);
        print_state(sesion, philo->id, "is eating");
        philo->last_meal = get_timestamp();
        philo->meals_eaten++;
        if (philo->meals_eaten >= sesion->max_meals)
        {
            sesion->run_simulation = 0;
            break;
        }
        usleep(sesion->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->left_fork->fork);
        pthread_mutex_unlock(&philo->right_fork->fork);
        print_state(sesion, philo->id, "is sleeping");
        usleep(sesion->time_to_sleep * 1000);
        print_state(sesion, philo->id, "is thinking");
    }
    return (NULL);
}

void    control_simulation(t_simulation *sesion)
{
    int i;
    int full_philo;
    long long no_eating_time;

    full_philo = 1;
    while (sesion->run_simulation)
    {
        i = 0;
        while (i < sesion->number_philos)
        {
            no_eating_time = get_timestamp() - sesion->philosophers[i].last_meal;
            if (no_eating_time > sesion->time_to_die)
            {
                print_state(sesion, sesion->philosophers[i].id, "died");
                sesion->run_simulation = 0;
                break ;
            }
            if (sesion->philosophers[i].meals_eaten < sesion->max_meals)
                full_philo = 0;
            i++;
        }
        if (sesion->max_meals > 0 && full_philo)
            sesion->run_simulation = 0;
        usleep(10000);
    }
}

void    start_simulation(t_simulation *sesion)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < sesion->number_philos)
    {
        pthread_create(&sesion->philosophers[i].thread_id, NULL, &philo_routine, &sesion->philosophers[i]);
        i++;
    }
    sesion->start_time = get_timestamp();
    control_simulation(sesion);
    while (j < sesion->number_philos)
    {
        pthread_join(sesion->philosophers[j].thread_id, NULL);
        j++;
    }
}
