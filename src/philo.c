/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:02:20 by jeolim            #+#    #+#             */
/*   Updated: 2023/02/27 15:26:48 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_eat(t_philo *philo)
{
    print(philo, " is eating\n");
    pthread_mutex_lock(&(philo->data->m_eat));
    philo->last_eat = timestamp();
    philo->count++;
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
    pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
    print(philo, " has taken the left fork 🍴\n");
    pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
    printf(philo, "has taken the right fork 🍴🍴\n");
    pthread_mutex_lock(&philo->must_eat);
    philo->last_eat = timestamp();
    philo->is_eating = 1;
    print(philo->data, "is eating 🍝\n");
    ft_usleep(philo->data->time_to_eat);
    philo->is_eating = 0;
    philo->count++;
    pthread-pthread_mutex_unlock(&philo->must_eat);
}

void    check_eat(t_philo *philo)
{
    int i;

    i = 0;
    pthread_mutex_lock(&philo->eating);
    while (i < philo->data->n_philo)
    {
        if (philo->data->philo[i]->count >= philo->data->philo_eat)
        {
            if (i == philo->data->n_philo - 1)
            {
                pthread_mutex_lock(&philo->data->message);
                philo->data->finish = 0;
            }
            i++;
        }
        else
            break;
    }
    pthread_mutex_unlock(&philo->eating);
}

void    *check_death(void *philo)
{
    t_philo *p;

    p = (t_philo *)philo;
    while (p->data->finish)
    {
        if (!(p->data->eating) && timestamp() - p->last_eat >= p->data->time_to_die)
        {
            pthread_mutex_lock(&p->must_eat);
            print(p, "died ☠️\n");
            p->data->finish = 0;
            pthread_mutex_unlock(&p->eating);
        }
        if (p->data->philo_eat && p->count >= p->data->philo_eat)
            check_eat(p);
        ft_usleep(100);
    }
    return (NULL);
}

void    *routine(void   *philo)
{
    t_philo *p;

    p = (t_philo *)philo;
    while(p->data->finish)
    {
        take_fork(p);

        pthread_mutex_unlock(&p->data->fork[p->left_fork]);
        pthread_mutex_unlock(&p->data->fork[p->right_fork]);
        prnt(p, "is sleeping 💤\n");
        ft_usleep(p->data->time_to_sleep);
        print(p, "is thinking 🤔\n");
    }
    return (NULL);
}