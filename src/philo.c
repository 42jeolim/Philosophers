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

void    take_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
    pirnt_message(philo, "has taken the left fork 🍴");
    pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
    pirnt_message(philo, "has taken the right fork 🍴🍴");
    pthread_mutex_lock(&philo->mutex_eating);
    philo->last_eat = timestamp();
    philo->is_eating = 1;
    pirnt_message(philo, "is eating 🍝");
    ft_usleep(philo->data->time_to_eat);
    philo->is_eating = 0;
    philo->count++;
    pthread_mutex_unlock(&philo->mutex_eating);
}

void    *routine(void   *philo)
{
    t_philo *tmp;

    tmp = (t_philo *)philo;
    while(tmp->data->finish)
    {
        take_fork(tmp);
        pthread_mutex_unlock(&tmp->data->fork[tmp->left_fork]);
        pthread_mutex_unlock(&tmp->data->fork[tmp->right_fork]);
        pirnt_message(tmp, "is sleeping 💤");
        ft_usleep(tmp->data->time_to_sleep);
        pirnt_message(tmp, "is thinking 🤔");
    }
    return (NULL);
}

void    check_eat(t_philo   *philo)
{
    int i;

    i = 0;
    pthread_mutex_lock(&philo->mutex_eating);
    while(i < philo->data->n_philo)
    {
        if (philo->data->philo[i]->count >= philo->data->must_eat)
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
    pthread_mutex_unlock(&philo->mutex_eating);
}

void    *check_death(void   *philo)
{
    t_philo *tmp;

    tmp = (t_philo *)philo;
    while (tmp->data->finish)
    {
        if (!(tmp->is_eating) && timestamp() - tmp->last_eat >= tmp->data->time_to_die)
        {
            pthread_mutex_lock(&tmp->mutex_eating);
            pirnt_message(tmp, "died ☠️");
            tmp->data->finish = 0;
            pthread_mutex_unlock(&tmp->mutex_eating);
        }
        if (tmp->data->must_eat && tmp->count >= tmp->data->must_eat)
            check_eat(tmp);
        ft_usleep(100);
    }
    return (NULL);
}

void    philo_work(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_philo)
    {
        data->philo[i]->last_eat = timestamp();
        pthread_create(&data->philo[i]->thread, NULL, routine, (void *)data->philo[i]);
        i++;
        usleep(100);
    }
    i = 0;
    while (i < data->n_philo)
    {
        pthread_create(&data->philo[i]->check_death_thread, NULL, check_death, (void *)data->philo[i]);
        i++;
        usleep(100);
    }
}