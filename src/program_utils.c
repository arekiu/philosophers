#include "philosophers.h"

long long get_timestamp() 
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
}

/*struct timeval (comes from sys/time.h) to hold the time
gettimeofday (stores current time, 2nd argument is timezone)
tv_sec converts seconds to milliseconds and tv_usec micro to milliseconds, makes adittion*/
void    print_state(t_simulation *sesion, int id, const char *state)
{
    long long current_time;
    long long elapsed_time;

    current_time = get_timestamp();
    elapsed_time = current_time - sesion->start_time;
    printf("%lld %d %s\n", elapsed_time, id, state);
}

void    clean_sesion(t_simulation *sesion)
{
    int i;

    i = 0;
    while (i < sesion->number_philos)
    {
        pthread_mutex_destroy(&sesion->forks[i].fork);
        i++;
    }
    free(sesion->forks);
    free(sesion->philosophers);
}