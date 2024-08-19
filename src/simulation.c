#include "philosophers.h"

void    *philo_routine(void *arg)
{
    t_philosopher *philo;
    t_simulation   *sesion;

    philo = (t_philosopher *)arg;
    sesion = philo->simulation;
    while (sesion->run_simulation)
    {
        /*if (philo->meals_eaten == sesion->max_meals)
            return (NULL);*/
        pthread_mutex_lock(&philo->left_fork->fork);
        print_state(sesion, philo->id, "has taken a fork");
        pthread_mutex_lock(&philo->right_fork->fork);
        print_state(sesion, philo->id, "has taken a fork");
        print_state(sesion, philo->id, "is eating");
        philo->last_meal = get_timestamp();
        printf("Philosopher %d: Last Meal Updated to %lld\n", philo->id, philo->last_meal);
        philo->meals_eaten++;
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
    long long no_eating_time, current_time;

    while (sesion->run_simulation)
    {
        i = 0;
        while (i < sesion->number_philos)
        {
            current_time = get_timestamp();
            no_eating_time = current_time - sesion->philosophers[i].last_meal;
            // Detailed debug output
            printf("Philosopher %d:\n", sesion->philosophers[i].id);
            printf("  Current Time: %lld\n", current_time);
            printf("  Last Meal Time: %lld\n", sesion->philosophers[i].last_meal);
            printf("  No Eating Time: %lld\n", no_eating_time);
            printf("  Time to Die: %d\n", sesion->time_to_die);
            if (no_eating_time > sesion->time_to_die)
            {
                print_state(sesion, sesion->philosophers[i].id, "died");
                sesion->run_simulation = 0;
                break ;
            }
            i++;
        }
        usleep(10000);
    }
    i = 0;
    while (i < sesion->number_philos)
    {
        pthread_join(sesion->philosophers[i].thread_id, NULL);
        i++;
    }
}

void    start_simulation(t_simulation *sesion)
{
    int i;

    i = 0;
    while (i < sesion->number_philos)
    {
        pthread_create(&sesion->philosophers[i].thread_id, NULL, philo_routine, &sesion->philosophers[i]);
        i++;
    }
    control_simulation(sesion);
}
