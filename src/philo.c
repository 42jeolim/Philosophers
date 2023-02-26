#include "philo.h"

void    philo_eat(t_philo *philo)
{
    print(philo, " is eating\n");
    pthread_mutex_lock(&(philo->data->m_eat));
    philo->last_eat = timestamp();
    philo->m_count++;
    pthread_mutex_unlock(&(philo->data->m_eat));
    ft_usleep(philo->data->time_to_eat);
    pthread_mutex_unlock((philo->right_fork));
    pthread_mutex_unlock(&(philo->left_fork));
    print(philo, " is sleeping\n");
    ft_usleep(philo->data->time_to_sleep);
    print(philo, " is thinking\n");
}

void    take_fork(t_philo *philo)
{
    pthread_mutex_lock(&(philo->left_fork));
    print(philo, " has taken a fork\n");
    if (philo->data->n_philo == 1)
    {
        ft_usleep(philo->data->time_to_die * 2);
        return ;
    }
    pthread_mutex_lock(&(philo->left_fork));
    print(philo, " has taken a fork\n");
}

void    *check_death(void *philo)
{
    t_philo *p;

    p = (t_philo *)philo;
    ft_usleep(p->data->time_to_die + 1);
    pthread_mutex_lock(&p->data->m_eat);
    pthread_mutex_lock(&p->data->m_stop);
    if (!is_dead(p, 0) && timestamp() - p->last_eat >= (long)(p->data->time_to_die))
    {
        pthread_mutex_unlock(&p->data->m_eat);
        pthread_mutex_unlock(&p->data->m_stop);
        print(p, " died\n");
        is_dead(p, 1);
    }
    pthread_mutex_unlock(&p->data->m_eat);
    pthread_mutex_unlock(&p->data->m_stop);
    return (NULL);
}

void    *philo_life(void *philo)
{
    t_philo     *p;
    pthread_t   t;

    p = (t_philo *)philo;
    if (p->id % 2 == 0) // 짝수일 때
        ft_usleep(p->data->time_to_eat / 10);
    while (!is_dead(p, 0))
    {
        pthread_create(&t, NULL, check_death, philo);
        take_fork(p);
        philo_eat(p);
        pthread_detach(t);
        if (p->m_count == p->data->n_eat)
        {
            pthread_mutex_lock(&p->data->m_stop);
            if (++p->data->philo_eat == p->data->n_philo)
            {
                pthread_mutex_unlock(&p->data->m_stop);
                is_dead(philo, 2);
            }
            pthread_mutex_unlock(&p->data->m_stop);
            return (NULL);
        }
    }
    return (NULL);
}