#include "philo.h"

int    error_print(char *str)
{
    int len;

    len = 0;
    while (str[len])
        len++;
    write(2, str, len);
    return (1);
}

void    print(t_philo *philo, char *str)
{
    long int    time;

    pthread_mutex_lock(&(philo->data->message));
    time = timestamp() - philo->data->t_start;
    if (!philo->data->finish && time >= 0 \
        && time <= 2147483647 && !is_dead(philo, 0))
        printf("%lld %d %s", timestamp() - philo->data->t_start, philo->id, str);
    pthread_mutex_unlock(&(philo->data->message));
}

int is_dead(t_philo *philo, int n)
{
    pthread_mutex_lock(&philo->data->dead);
    if (n)
        philo->data->finish = 1;
    if (philo->data->finish)
    {
        pthread_mutex_unlock(&philo->data->dead);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->dead);
    return (0);
}

void    ft_usleep(int ms)
{
    long int    time;

    time = timestamp();
    while (timestamp() - time < ms)
        usleep(ms / 10);
}

long long   timestamp(void)
{
    struct timeval   tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}